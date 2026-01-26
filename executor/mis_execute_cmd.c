/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_execute_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:41:01 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/25 16:16:23 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_builtin_cmd(t_command *cmd, t_minishell *shell)
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
	else
		mis_exec(cmd, shell);
}

static int	execute_redirs_cmd(t_command *cmd, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell->exit_status = 1;
		return (0);
	}
	if (pid == 0)
	{
		setchild_signals();
		if (mis_redirections(cmd->redirs) == -1)
			exit(1);
		execute_builtin_cmd(cmd, shell);
		exit(shell->exit_status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (0);
}

void	execute_command(t_command *cmd, t_minishell *shell)
{
	t_command	*cur;
	int			all_empty;

	all_empty = 1;
	cur = cmd;
	while (cur)
	{
		if (cur->args && cur->args[0])
		{
			all_empty = 0;
			if (cur->redirs)
				execute_redirs_cmd(cur, shell);
			else
				execute_builtin_cmd(cur, shell);
		}
		cur = cur->next;
	}
	if (all_empty)
		shell->exit_status = 0;
}
