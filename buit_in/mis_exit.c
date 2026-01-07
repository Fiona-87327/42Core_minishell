/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:54:41 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/05 19:54:53 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mis_exit(t_command *cmd, t_minishell *shell)
{
	int	exit_code;

	(void)shell;
	if (cmd->args[1] == NULL)
	{
		exit_code = 0;
	}
	else
	{
		exit_code = ft_atoi(cmd->args[1]);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_code);
}
