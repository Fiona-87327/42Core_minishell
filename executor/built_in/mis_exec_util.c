/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_exec_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:35:25 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/02 12:54:55 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_with_error(char *cmd, char *msg, int code, t_minishell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free_cmds(shell->cmds);
	ft_free_array(shell->env);
	exit(code);
}

void	handle_exec_error(char *cmd, t_minishell *shell)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		exit_with_error(cmd, "Is a directory", 126, shell);
	if (errno == EACCES)
		exit_with_error(cmd, "Permission denied", 126, shell);
	exit_with_error(cmd, "No such file or directory", 127, shell);
}

void	check_directory(char *path, t_minishell *shell)
{
	struct stat	st;

	if ((ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0))
		return ;
	if (ft_strchr(path, '/') && stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		free_cmds(shell->cmds);
		ft_free_array(shell->env);
		exit(126);
	}
}

void	mis_exec_dot_error(t_minishell *shell)
{
	ft_putstr_fd("minishell: .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	free_cmds(shell->cmds);
	ft_free_array(shell->env);
	exit(2);
}

void	mis_exec_cmd_not_found(char *cmd, t_minishell *shell)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	shell->exit_status = 127;
	ft_free_array(shell->env);
	free_cmds(shell->cmds);
	exit(127);
}
