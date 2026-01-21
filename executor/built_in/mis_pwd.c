/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:51:46 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/21 11:36:17 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mis_pwd(t_command *cmd, t_minishell *shell)
{
	char	*cwd;

	(void)cmd;
	cwd = malloc(sizeof(char) * PATH_MAX);
	if (!cwd)
		return ;
	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		shell->exit_status = 0;
	}
	else
	{
		ft_putstr_fd("pwd: error retrieving current directory\n",
			STDERR_FILENO);
		shell->exit_status = 1;
	}
	free(cwd);
}
