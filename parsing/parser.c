/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:44:22 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/16 17:03:42 by mhnatovs         ###   ########.fr       */
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
	cmd->pipe_out = 0;
	cmd->append = 0;
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
	cmd->next = NULL;
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
		new_args[0] = strdup(word);
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

t_command	*parse_tokens(t_token *t, t_minishell *sh)
{
	t_command	*cmds;
	t_command	*current;
	// char		*exp_cmd;
	(void)sh;
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
		{
			// exp_cmd = expand_word(t->value, sh);
			// add_arg_to_cmd(current, exp_cmd);
			 add_arg_to_cmd(current, t->value); 
			// free(exp_cmd);
		}
		else if (t->type == PIPE)
		{
			current->pipe_out = 1;
			current = NULL;
		}
		else if (t->type == REDIR_OUT || t->type == REDIR_APPEND)
		{
			current->redir_out = ft_strdup(t->next->value);
			current->append = (t->type == REDIR_APPEND);
			t = t->next;
		}
		else if (t->type == REDIR_IN)
		{
			current->redir_in = ft_strdup(t->next->value);
			t = t->next;
		}
		t = t->next;
	}
	/*// DEBUG:
    printf("\n=== AFTER PARSING ===\n");
    t_command *debug_cmd = cmds;
    int cmd_idx = 0;
    while (debug_cmd)
    {
        printf("Command %d:\n", cmd_idx);
        int i = 0;
        while (debug_cmd->args && debug_cmd->args[i])
        {
            printf("  args[%d] = [%s]\n", i, debug_cmd->args[i]);
            i++;
        }
        if (debug_cmd->redir_in)
            printf("  redir_in = [%s]\n", debug_cmd->redir_in);
        if (debug_cmd->redir_out)
            printf("  redir_out = [%s]\n", debug_cmd->redir_out);
        printf("  pipe_out = %d\n", debug_cmd->pipe_out);
        debug_cmd = debug_cmd->next;
        cmd_idx++;
    }
    printf("=====================\n\n");*/
	return (cmds);
}
