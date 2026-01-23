/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:30:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/21 20:07:15 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_paths(paths), path);
		free(path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

static void	handle_exec_error(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	exit(127);
}

void	mis_exec_cmd(t_command *cmd, t_minishell *shell)
{
	char	*path;

	if (mis_redirections(cmd->redirs) == -1)
		exit(1);
	if (ft_strchr(cmd->args[0], '/'))
		path = cmd->args[0];
	else
		path = get_path(cmd->args[0], shell->env);
	if (!path || access(path, F_OK) != 0)
		handle_exec_error(cmd->args[0]);
	execve(path, cmd->args, shell->env);
	perror("execve");
	exit(1);
}

void	mis_exec(t_command *cmd, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		setchild_signals();
		mis_exec_cmd(cmd, shell);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}
