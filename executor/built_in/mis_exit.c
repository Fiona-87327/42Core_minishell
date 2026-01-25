/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:54:41 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/25 12:58:07 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	unsigned long long	result;
	int					sign;
	int					i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((long long)(result * sign));
}

// void	mis_exit(t_command *cmd, t_minishell *shell)
// {
// 	ft_putstr_fd("exit\n", STDOUT_FILENO);
// 	if (cmd->args[1])
// 	{
// 		if (!is_numeric(cmd->args[1]))
// 		{
// 			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
// 			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
// 			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
// 			shell->exit_status = 2;
// 			return ;
// 		}
// 		if (cmd->args[2])
// 		{
// 			ft_putstr_fd("minishell: exit: too many arguments\n",
// 				STDERR_FILENO);
// 			shell->exit_status = 1;
// 			return ;
// 		}
// 		shell->exit_status = (unsigned char)ft_atoll(cmd->args[1]);
// 		return ;
// 	}
// 	return ;
// }

void	mis_exit(t_command *cmd, t_minishell *shell)
{
	long long	status;

	ft_putstr_fd("exit\n", 2);
	if (!cmd || !cmd->args[1])
		exit(shell->exit_status);
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return ;
	}
	status = ft_atoll(cmd->args[1]);
	exit((unsigned char)status);
}
