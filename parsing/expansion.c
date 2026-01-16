/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:01:07 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/16 17:03:05 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_from_shell(char *name, t_minishell *shell)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
		{
			return (ft_strdup(shell->env[i] + len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

// static char	*expand_arg(char *arg, t_minishell *shell)
// {
// 	if (ft_strcmp(arg, "$?") == 0)
// 		return (ft_itoa(shell->exit_status));
// 	if (arg[0] == '$' && arg[1])
// 		return (get_env_from_shell(arg + 1, shell));
// 	return (ft_strdup(arg));
// }

char *get_name_for_var(char *word, int *i)
{
	int start;
	int len;
	char *var_name;

	start = *i;
	len = 0;
	if (!word[*i] || (!ft_isalpha(word[*i]) && word[*i] != '_'))
		return (NULL);
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
	{
		len++;
		(*i)++;
	}
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, &word[start], len + 1);
	return (var_name);
}

char *expand_word(char *word, t_minishell *shell)
{
	int i = 0;
	t_quotes quote = NOT_IN_QUOTES;
	char *res = ft_strdup("");
	char *temp;

	while (word[i])
	{
		if (word[i] == '\'' && quote != IN_DOUBLE_QUOTES)
			quote = (quote == IN_SINGLE_QUOTES) ? NOT_IN_QUOTES : IN_SINGLE_QUOTES;
		else if (word[i] == '"' && quote != IN_SINGLE_QUOTES)
			quote = (quote == IN_DOUBLE_QUOTES) ? NOT_IN_QUOTES : IN_DOUBLE_QUOTES;
		else if (word[i] == '$' && quote != IN_SINGLE_QUOTES)
		{
			i++;
			if (word[i] == '?')
			{
				temp = res;
				res = ft_strjoin(temp, ft_itoa(shell->exit_status));
				free(temp);
				i++;
			}
			else
			{
				char *var_name = get_name_for_var(word, &i);
				if (var_name)
				{
					char *value = get_env_from_shell(var_name, shell);
					temp = res;
					res = ft_strjoin(temp, value);
					free(temp);
					free(var_name);
					free(value);
				}
				else
				{
					temp = res;
					res = ft_strjoin_char(temp, '$');
					free(temp);
				}
			}
		}
		else
		{
			temp = res;
			res = ft_strjoin_char(temp, word[i]);
			free(temp);
			i++;
		}
	}
	return res;
}


char	**expand_args(char **args, t_minishell *shell)
{
	int		i;
	char	**ptrs;
	int		size;

	i = 0;
	size = ft_arraylen(args);
	ptrs = malloc(sizeof(char *) * (size + 1));
	if (!ptrs)
		return (NULL);
	while (args[i])
	{
		ptrs[i] = expand_word(args[i], shell);
		i++;
	}
	ptrs[i] = NULL;
	return (ptrs);
}

void expand_cmds(t_command *cmds, t_minishell *sh)
{
	t_command *cmd;
	int i;
	char *tmp;

	cmd = cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			tmp = expand_word(cmd->args[i], sh);
			free(cmd->args[i]);
			cmd->args[i] = delete_quotes(tmp);
			free(tmp);
			i++;
		}
		if (cmd->redir_in)
		{
			tmp = cmd->redir_in;
			cmd->redir_in = delete_quotes(tmp);
			free(tmp);
		}
		if (cmd->redir_out)
		{
			tmp = cmd->redir_out;
			cmd->redir_out = delete_quotes(tmp);
			free(tmp);
		}
		cmd = cmd->next;
	}
}
	
// void expand_cmds(t_command *cmds, t_minishell *sh)
// {
//     t_command *cmd;
//     int i;
//     char *tmp;

//     cmd = cmds;
//     printf("\n=== EXPANSION START ===\n");
//     while (cmd)
//     {
//         i = 0;
//         while (cmd->args && cmd->args[i])
//         {
//             printf("BEFORE expand: args[%d] = [%s]\n", i, cmd->args[i]);
            
//             tmp = expand_word(cmd->args[i], sh);
//             printf("AFTER expand_word: [%s]\n", tmp);
            
//             free(cmd->args[i]);
//             cmd->args[i] = delete_quotes(tmp);
//             printf("AFTER delete_quotes: [%s]\n", cmd->args[i]);
            
//             free(tmp);
//             i++;
//         }
//         cmd = cmd->next;
//     }
//     printf("=== EXPANSION END ===\n\n");
// }