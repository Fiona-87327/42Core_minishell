/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:25:15 by jiyan             #+#    #+#             */
/*   Updated: 2026/01/23 15:31:19 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	find_newline(const char *s)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*extract_line(char *line)
{
	size_t	len;
	char	*new_line;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (line[len] == '\n')
		len++;
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	ft_memmove(new_line, line, len);
	new_line[len] = '\0';
	return (new_line);
}

static void	update_stash(char *stash)
{
	ssize_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		ft_memmove(stash, &stash[i + 1], ft_strlen(&stash[i + 1]) + 1);
}

static char	*_b_read(int fd, char *buffer, char *line, int *bytes_read)
{
	char	*tmp;

	*bytes_read = 1;
	while (*bytes_read != 0 && find_newline(line) < 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read < 0)
		{
			ft_memmove(buffer, "\0", 1);
			free(line);
			return (NULL);
		}
		buffer[*bytes_read] = '\0';
		tmp = ft_strjoin(line, buffer);
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = tmp;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_memmove(stash, "\0", 1);
		return (NULL);
	}
	line = ft_strdup(stash);
	if (!line)
		return (NULL);
	line = _b_read(fd, stash, line, &bytes_read);
	if (!line)
		return (NULL);
	if (bytes_read == 0 && ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	tmp = extract_line(line);
	update_stash(stash);
	free(line);
	return (tmp);
}
