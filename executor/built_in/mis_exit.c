/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:54:41 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/27 19:11:45 by jiyawang         ###   ########.fr       */
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

static int	handle_non_numeric_exit(char *arg, t_minishell *shell)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	shell->exit_status = 2;
	shell->should_exit = 1;
	return (1);
}

static int	handle_too_many_args(t_minishell *shell)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	shell->exit_status = 1;
	shell->should_exit = 1;
	return (1);
}

void	mis_exit(t_command *cmd, t_minishell *shell)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
			if (handle_non_numeric_exit(cmd->args[1], shell))
				return ;
		if (cmd->args[2])
			if (handle_too_many_args(shell))
				return ;
		shell->exit_status = (unsigned char)ft_atoll(cmd->args[1]);
		shell->should_exit = 1;
		return ;
	}
	shell->should_exit = 1;
}
