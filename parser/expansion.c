/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:01:07 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/19 16:59:14 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_from_shell(char *name, t_minishell *shell)
{
	int	i;
	int	len;

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
	int			i;
	t_quotes	quote;
	char		*res;

	quote = NOT_IN_QUOTES;
	res = ft_strdup("");
	i = 0;
	while (word[i])
	{
		if (handle_quotes(word[i], &quote))
			res = append_char(res, word[i++]);
		else if (word[i] == '$' && quote != IN_SINGLE_QUOTES)
			res = dollar_expan(word, shell, &i, res);
		else
		{
			res = append_char(res, word[i]);
			i++;
		}
	}
	return (res);
}

static void	redirs_delete_quotes(t_command *cmd)
{
	char	*temp;

	if (cmd->redir_in)
	{
		temp = cmd->redir_in;
		cmd->redir_in = delete_quotes(temp);
		free(temp);
	}
	if (cmd->redir_out)
	{
		temp = cmd->redir_out;
		cmd->redir_out = delete_quotes(temp);
		free(temp);
	}
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
		redirs_delete_quotes(cmd);
		cmd = cmd->next;
	}
}
