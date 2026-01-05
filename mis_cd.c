/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:45:31 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/05 19:47:22 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mis_cd(t_command *cmd, t_minishell *shell)
{
	char	*home;

	(void)shell;
	if (cmd->args[1] == NULL)
	{
		home = getenv("HOME");
		if (home)
			chdir(home);
		else
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	}
	else
	{
		if (chdir(cmd->args[1]) != 0)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
	}
}
