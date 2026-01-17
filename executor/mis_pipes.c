/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:09:32 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/17 18:27:48 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(t_command *cmd)
{
	int	len;

	len = 0;
	while (cmd)
	{
		len++;
		cmd = cmd->next;
	}
	return (len);
}

static void	close_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	create_pipes(int ***pipes, int num_pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * num_pipes);
	i = 0;
	while (i < num_pipes)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (pipe((*pipes)[i]) == -1)
			perror("pipe");
		i++;
	}
}

static void	setup_pipe_fds(int **pipes, int cmd_index, int num_commands)
{
	if (cmd_index > 0)
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	if (cmd_index < num_commands - 1)
	{
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
	close_pipes(pipes, num_commands - 1);
}

static void	execute_child_command(t_command *cmd, t_minishell *shell)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0 || \
		ft_strncmp(cmd->args[0], "echo", 5) == 0 || \
		ft_strncmp(cmd->args[0], "cd", 3) == 0 || \
		ft_strncmp(cmd->args[0], "env", 4) == 0 || \
		ft_strncmp(cmd->args[0], "exit", 5) == 0 || \
		ft_strncmp(cmd->args[0], "export", 7) == 0 || \
		ft_strncmp(cmd->args[0], "unset", 6) == 0)
	{
		if (mis_redirections(cmd->redirs) == -1)
			exit(1);
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
		exit(shell->exit_status);
	}
	else
		mis_exec_cmd(cmd, shell);
}

void	mis_pipes(t_command *cmd, t_minishell *shell)
{
	int		num_commands;
	int		**pipes;
	int		cmd_index;
	pid_t	pid;

	num_commands = count_commands(cmd);
	create_pipes(&pipes, num_commands - 1);
	cmd_index = 0;
	while (cmd)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			setup_pipe_fds(pipes, cmd_index, num_commands);
			execute_child_command(cmd, shell);
		}
		cmd = cmd->next;
		cmd_index++;
	}
	close_pipes(pipes, num_commands - 1);
	while (num_commands-- > 0)
		wait(NULL);
	// TODO: free pipes
}
