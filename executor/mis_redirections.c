/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:29:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/16 15:36:13 by jiyawang         ###   ########.fr       */
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
		perror("minishell: open");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	redirect_input(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell: open");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	redirect_heredoc(t_redir *redir)
{
	if (redir->heredoc_fd < 0)
	{
		perror("minishell: heredoc");
		return (-1);
	}
	if (dup2(redir->heredoc_fd, STDIN_FILENO) < 0)
	{
		perror("minishell: dup2");
		return (-1);
	}
	close(redir->heredoc_fd);
	return (0);
}

int	mis_redirections(t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (current->type == REDIRECT_OUTPUT
			|| current->type == REDIRECT_APPEND)
		{
			if (redirect_output(current) < 0)
				return (-1);
		}
		else if (current->type == REDIRECT_INPUT)
		{
			if (redirect_input(current) < 0)
				return (-1);
		}
		else if (current->type == REDIRECT_HEREDOC)
		{
			if (redirect_heredoc(current) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
