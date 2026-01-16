/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:29:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/16 17:02:59 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_output(t_redir *redir)
{
	int	fd;
	int	flags;

	if (redir->type == REDIRECT_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->filename, flags, 0644);
	if (fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	redirect_intput(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->filename);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redirect_heredoc(t_redir *redir)
{
	if (redir->heredoc_fd < 0)
	{
		perror("heredoc");
		return (-1);
	}
	dup2(redir->heredoc_fd, STDIN_FILENO);
	close(redir->heredoc_fd);
	return (0);
}
int	mis_redirections(t_redir *redir)
{
	t_redir	*current;
	int		result;

	current = redir;
	while (current)
	{
		if (current->type == REDIRECT_INPUT)
			result = redirect_intput(current);
		else if (current->type == REDIRECT_OUTPUT
			|| current->type == REDIRECT_APPEND)
			result = redirect_output(current);
		else if (current->type == REDIRECT_HEREDOC)
			result = redirect_heredoc(current);
		else
			result = -1;
		if (result < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}
