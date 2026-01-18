/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:44:22 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/18 17:06:28 by mhnatovs         ###   ########.fr       */
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

static int	add_arg_to_new_arr(t_command *cmd, char *word)
{
	char	**args;

	args = malloc(sizeof(char *) * 2);
	if (!args)
		return (1);
	args[0] = ft_strdup(word);
	if (!args[0])
	{
		free(args);
		return (1);
	}
	args[1] = NULL;
	cmd->args = args;
	return (0);
}

int	add_arg_to_cmd(t_command *cmd, char *word)
{
	char	**new_args;
	int		i;

	if (cmd->args == NULL)
		return (add_arg_to_new_arr(cmd, word));
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
	if (!new_args[i])
	{
		free(new_args);
		return (1);
	}
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (0);
}

static int	handle_token(t_token **t, t_command **current, t_command **cmds)
{
	if (!*current)
	{
		*current = new_command();
		command_add_back(cmds, *current);
	}
	if ((*t)->type == WORD)
	{
		if (add_arg_to_cmd(*current, (*t)->value))
			return (1);
	}
	else if ((*t)->type == PIPE)
	{
		*current = NULL;
	}
	else if (is_redir((*t)->type))
	{
		if (handle_redir(*current, *t))
			return (1);
		*t = (*t)->next;
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
		if (handle_token(&t, &current, &cmds))
			return (NULL);
		t = t->next;
	}
	return (cmds);
}
