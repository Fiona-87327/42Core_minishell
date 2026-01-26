/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:54:14 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/26 13:45:33 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mis_env(t_command *cmd, t_minishell *shell)
{
	char		**env;

	(void)cmd;
	env = shell->env;
	while (*env)
	{
		if (ft_strchr(*env, '='))
		{
			ft_putstr_fd(*env, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		env++;
	}
}

char	**init_min_env(void)
{
	char	**env;
	char	*cwd;

	env = malloc(sizeof(char *) * 4);
	cwd = getcwd(NULL, 0);
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	free(cwd);
	return (env);
}
