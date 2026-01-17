/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:01:07 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/17 19:38:20 by mhnatovs         ###   ########.fr       */
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

char	*get_name_for_var(char *word, int *i)
{
	int		start;
	int		len;
	char	*var_name;

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

char	*expand_word(char *word, t_minishell *shell)
{
	int	i;

	t_quotes quote = NOT_IN_QUOTES;
	char *res = ft_strdup("");
	char *temp;
	char *var_name;
	char *value;
	i = 0;

	while (word[i])
	{
		if (word[i] == '\'' && quote != IN_DOUBLE_QUOTES)
		{
			if (quote == IN_SINGLE_QUOTES)
				quote = NOT_IN_QUOTES;
			else
				quote = IN_SINGLE_QUOTES;
			temp = res;
			res = ft_strjoin_char(temp, word[i]);
			free(temp);
			i++;
		}
		else if (word[i] == '"' && quote != IN_SINGLE_QUOTES)
		{
			if(quote == IN_DOUBLE_QUOTES)
				quote = NOT_IN_QUOTES;
			else
				quote = IN_DOUBLE_QUOTES;
			temp = res;
			res = ft_strjoin_char(temp, word[i]);
			free(temp);
			i++;
		}
		else if (word[i] == '$' && quote != IN_SINGLE_QUOTES)
		{
			i++;
			if (word[i] == '?')
			{
				temp = res;
				value = ft_itoa(shell->exit_status);
				res = ft_strjoin(temp, value);
				free(temp);
				free(value);
				i++;
			}
			else if (ft_isalpha(word[i]) || word[i] == '_')
			{
				var_name = get_name_for_var(word, &i);
				if (var_name)
				{
					value = get_env_from_shell(var_name, shell);
					temp = res;
					res = ft_strjoin(temp, value);
					free(temp);
					free(var_name);
					free(value);
				}
			}
			else
			{
				temp = res;
				res = ft_strjoin_char(temp, '$');
				free(temp);
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
	return (res);
}

void	expand_cmds(t_command *cmds, t_minishell *sh)
{
	t_command	*cmd;
	int			i;
	char		*tmp;

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
