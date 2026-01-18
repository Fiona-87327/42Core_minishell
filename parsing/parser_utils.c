/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:58:29 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/18 17:02:40 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	is_redir(t_token_type type)
{
	return (type == REDIR_OUT || type == REDIR_APPEND
		|| type == REDIR_IN || type == HEREDOC);
}

t_redir	*add_redir_define_type(t_token_type type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	if (type == REDIR_IN)
		new->type = REDIRECT_INPUT;
	else if (type == REDIR_OUT)
		new->type = REDIRECT_OUTPUT;
	else if (type == REDIR_APPEND)
		new->type = REDIRECT_APPEND;
	else if (type == HEREDOC)
		new->type = REDIRECT_HEREDOC;
	else
		new->type = REDIRECT_INPUT;
	new->heredoc_fd = -1;
	new->next = NULL;
	return (new);
}

int	add_redir(t_command *cmd, t_token_type type, char *filename)
{
	t_redir	*new;
	t_redir	*last;

	new = add_redir_define_type(type);
	if (!new)
		return (1);
	new->filename = ft_strdup(filename);
	if (!new->filename)
	{
		free(new);
		return (1);
	}
	if (!cmd->redirs)
		cmd->redirs = new;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (0);
}

int	handle_redir(t_command *cmd, t_token *token)
{
	if (!token->next || token->next->type != WORD)
		return (1);
	if (add_redir(cmd, token->type, token->next->value))
		return (1);
	return (0);
}
