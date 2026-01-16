/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:36:37 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/16 17:10:35 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_add_back(t_command **lst, t_command *new)
{
	t_command	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->redirs = NULL;
	return (cmd);
}

int	add_arg_to_cmd(t_command *cmd, char *word)
{
	char	**new_args;
	int		i;

	if (cmd->args == NULL)
	{
		new_args = malloc(sizeof(char *) * 2);
		if (!new_args)
			return (1);
		new_args[0] = ft_strdup(word);
		new_args[1] = NULL;
		cmd->args = new_args;
		return (0);
	}
	i = ft_arraylen(cmd->args);
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (1);
	i = 0;
	while (cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(word);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (0);
}

int	add_redir(t_command *cmd, t_token_type type, char *filename)
{
	t_redir	*new;
	t_redir	*last;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (1);
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
	new->filename = ft_strdup(filename);
	new->heredoc_fd = -1;
	new->next = NULL;
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

t_command	*parse_tokens(t_token *t)
{
	t_command	*cmds;
	t_command	*current;

	cmds = NULL;
	current = NULL;
	while (t)
	{
		if (!current)
		{
			current = new_command();
			command_add_back(&cmds, current);
		}
		if (t->type == WORD)
			add_arg_to_cmd(current, t->value);
		else if (t->type == PIPE)
		{
			current = NULL;
		}
		else if (t->type == REDIR_OUT || t->type == REDIR_APPEND 
			|| t->type == REDIR_IN || t->type == HEREDOC)
		{
			if (t->next && t->next->type == WORD)
			{
				add_redir(current, t->type, t->next->value);
				t = t->next;
			}
		}
		t = t->next;
	}
	return (cmds);
}
