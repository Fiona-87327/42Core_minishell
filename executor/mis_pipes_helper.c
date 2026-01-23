/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_pipes_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:54:43 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/23 15:57:25 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}

static void	run_builtin(t_command *cmd, t_minishell *shell)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		mis_pwd(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		mis_echo(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		mis_cd(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		mis_env(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		mis_exit(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		mis_export(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		mis_unset(cmd, shell);
}

void	execute_child_command(t_command *cmd, t_minishell *shell)
{
	if (is_builtin(cmd->args[0]))
	{
		if (mis_redirections(cmd->redirs) == -1)
			exit(1);
		run_builtin(cmd, shell);
		exit(shell->exit_status);
	}
	else
		mis_exec_cmd(cmd, shell);
}

void	free_pipes_memory(int **pipes, int num_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	wait_all_children(pid_t last_pid, t_minishell *shell)
{
	int		status;
	pid_t	current_pid;
	int		last_status;

	last_status = 0;
	while (1)
	{
		current_pid = wait(&status);
		if (current_pid <= 0)
			break ;
		if (current_pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
	}
	shell->exit_status = last_status;
}
