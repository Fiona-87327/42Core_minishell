/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:30:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/24 15:07:35 by jiyawang         ###   ########.fr       */
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
	perror("minishell");
	exit(127);
}

void	mis_exec_cmd(t_command *cmd, t_minishell *shell)
{
	char	*path;
	char	**actual_args;

	if (!cmd || !cmd->args)
		exit(0);
	actual_args = cmd->args;
	while (*actual_args && **actual_args == '\0')
		actual_args++;
	if (!*actual_args)
		exit(0);
	if (mis_redirections(cmd->redirs) == -1)
		exit(1);
	if (ft_strchr(*actual_args, '/'))
		path = *actual_args;
	else
		path = get_path(*actual_args, shell->env);
	if (!path)
	{
		ft_putstr_fd(*actual_args, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, actual_args, shell->env);
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
