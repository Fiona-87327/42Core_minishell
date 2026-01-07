/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:53:38 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/07 13:09:14 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mis_unset(t_command *cmd, t_minishell *shell)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;

	i = 1;
	while (cmd->args[i])
	{
		j = 0;
		k = 0;
		new_env = malloc(sizeof(char *) * (ft_arraylen(shell->env) + 1));
		while (shell->env[j])
		{
			if (ft_strncmp(shell->env[j], cmd->args[i],
					ft_strlen(cmd->args[i])) != 0)
				new_env[k++] = ft_strdup(shell->env[j]);
			j++;
		}
		new_env[k] = NULL;
		ft_free_array(shell->env);
		shell->env = new_env;
		i++;
	}
}
