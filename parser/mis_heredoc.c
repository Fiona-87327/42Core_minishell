/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:35:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/26 12:11:47 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_line(char *line, int fd, t_minishell *shell,
		int quoted)
{
	char	*expanded_line;

	if (!quoted)
		expanded_line = expand_word(line, shell);
	else
		expanded_line = ft_strdup(line);
	ft_putendl_fd(expanded_line, fd);
	free(expanded_line);
}

static char	*get_heredoc_line(void)
{
	char	*line;
	char	*tmp;

	if (isatty(STDIN_FILENO))
		return (readline("> "));
	tmp = get_next_line(STDIN_FILENO);
	if (!tmp)
		return (NULL);
	line = ft_strtrim(tmp, "\n");
	free(tmp);
	return (line);
}

static int	heredoc_is_quoted(const char *delim)
{
	while (*delim)
	{
		if (*delim == '\'' || *delim == '"')
			return (1);
		delim++;
	}
	return (0);
}

static int	read_heredoc(const char *delimiter, t_minishell *shell)
{
	int		fd[2];
	char	*line;
	char	*clean_delim;
	int		quoted;

	quoted = heredoc_is_quoted(delimiter);
	clean_delim = delete_quotes((char *)delimiter);
	if (pipe(fd) == -1)
		return (free(clean_delim), -1);
	while (1)
	{
		line = get_heredoc_line();
		if (!line)
			break ;
		if (ft_strncmp(line, clean_delim, ft_strlen(clean_delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		handle_heredoc_line(line, fd[1], shell, quoted);
		free(line);
	}
	free(clean_delim);
	close(fd[1]);
	return (fd[0]);
}

void	process_heredocs(t_command *cmds, t_minishell *shell)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIRECT_HEREDOC)
				redir->heredoc_fd = read_heredoc(redir->filename, shell);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
