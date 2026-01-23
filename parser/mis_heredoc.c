/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:35:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/23 15:46:14 by jiyawang         ###   ########.fr       */
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

// static int	read_heredoc(const char *delimiter, t_minishell *shell)
// {
// 	int		fd[2];
// 	char	*line;
// 	int		quoted;

// 	quoted = is_quote(delimiter[0]);
// 	if (pipe(fd) == -1)
// 		return (-1);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		handle_heredoc_line(line, fd[1], shell, quoted);
// 		free(line);
// 	}
// 	return (close(fd[1]), (fd[0]));
// }

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

static int	read_heredoc(const char *delimiter, t_minishell *shell)
{
	int		fd[2];
	char	*line;
	int		quoted;

	quoted = is_quote(delimiter[0]);
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = get_heredoc_line();
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		handle_heredoc_line(line, fd[1], shell, quoted);
		free(line);
	}
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
