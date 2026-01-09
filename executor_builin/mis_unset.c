/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:53:38 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/07 16:47:20 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_var_len(char **env, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && (env[i][len] == '='
			|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

static char	**remove_env_row(char **old_env, int var_index)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	len = ft_arraylen(old_env);
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (old_env[i])
	{
		if (i != var_index)
		{
			new_env[j] = old_env[i];
			j++;
		}
		else
			free(old_env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(old_env);
	return (new_env);
}

void	mis_unset(t_command *cmd, t_minishell *shell)
{
	int		i;
	int		var_index;
	char	**new_env;

	i = 1;
	while (cmd->args[i])
	{
		var_index = get_var_len(shell->env, cmd->args[i]);
		if (var_index != -1)
		{
			new_env = remove_env_row(shell->env, var_index);
			shell->env = new_env;
		}
		i++;
	}
	shell->exit_status = 0;
}
