/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_export1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:36:10 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/07 15:38:22 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(t_minishell *shell, char *arg)
{
	char	*name;
	int		i;
	int		len;
	char	**new_env;

	name = get_var_name(arg);
	if (!name)
		return ;
	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& (shell->env[i][len] == '=' || shell->env[i][len] == '\0'))
		{
			if (ft_strchr(arg, '='))
			{
				free(shell->env[i]);
				shell->env[i] = ft_strdup(arg);
			}
			free(name);
			return ;
		}
		i++;
	}
	free(name);
	i = ft_arraylen(shell->env);
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
}
