/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:30:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/26 17:15:33 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	if (!cmd || cmd[0] == '\0')
		return (NULL);
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
	return (free_paths(paths), NULL);
}

static void	handle_exec_error(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

static void	check_directory(char *path)
{
	struct stat	st;

	if ((ft_strcmp(path, ".") == 0 || ft_strcmp(path, "..") == 0))
		return ;
	if (ft_strchr(path, '/') && stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
}

static void	mis_exec_dot_error(void)
{
	ft_putstr_fd("minishell: .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	exit(2);
}

static void	mis_exec_cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

static char	*mis_exec_get_path(t_command *cmd, t_minishell *shell)
{
	if (ft_strchr(cmd->args[0], '/'))
		return (cmd->args[0]);
	return (get_path(cmd->args[0], shell->env));
}

void	mis_exec_cmd(t_command *cmd, t_minishell *shell)
{
	char	*path;

	if (cmd->args && cmd->args[0] && ft_strcmp(cmd->args[0], ".") == 0
		&& !cmd->args[1])
		mis_exec_dot_error();
	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	if (mis_redirections(cmd->redirs) == -1)
		exit(1);
	check_directory(cmd->args[0]);
	path = mis_exec_get_path(cmd, shell);
	if (!path || ft_strcmp(cmd->args[0], ".") == 0 || ft_strcmp(cmd->args[0],
			"..") == 0)
		mis_exec_cmd_not_found(cmd->args[0]);
	execve(path, cmd->args, shell->env);
	handle_exec_error(path);
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
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	setparent_signals();
	handle_child_status(status, shell);
}
