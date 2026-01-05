/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:30:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/05 20:50:48 by jiyawang         ###   ########.fr       */
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
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

void	mis_exec(t_command *cmd, t_minishell *shell)
{
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (ft_strchr(cmd->args[0], '/'))
			path = cmd->args[0];
		else
			path = get_path(cmd->args[0], shell->env);
		if (!path || access(path, F_OK) != 0)
		{
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			exit(127);
		}
		execve(path, cmd->args, shell->env);
		perror("execve");
		exit(1);
	}
	waitpid(pid, NULL, 0);
}
