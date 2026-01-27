/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:45:31 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/27 11:35:56 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_minishell *shell, char *key, char *value)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		return ;
	add_to_env(shell, entry);
	free(entry);
}

static char	*handle_cd_args(char *arg, t_minishell *shell)
{
	char	*dir;

	if (!arg || (ft_strncmp(arg, "~", 2) == 0))
	{
		dir = get_env_value(shell->env, "HOME");
		if (!dir)
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (dir);
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		dir = get_env_value(shell->env, "OLDPWD");
		if (!dir)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		else
			ft_putendl_fd(dir, STDOUT_FILENO);
		return (dir);
	}
	return (arg);
}

static void	update_pwds(t_minishell *shell, char *old_pwd)
{
	char	pwd[PATH_MAX];

	update_pwd(shell, "OLDPWD", old_pwd);
	if (getcwd(pwd, PATH_MAX))
		update_pwd(shell, "PWD", pwd);
}

static void	perform_cd_exec(t_minishell *shell, char *dir, char *arg, char *old)
{
	struct stat	st;

	if (chdir(dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		if (access(dir, F_OK) != 0)
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		else
		{
			stat(dir, &st);
			if (!S_ISDIR(st.st_mode))
				ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
			else if (access(dir, X_OK) != 0)
				ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			else
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		shell->exit_status = 1;
	}
	else
	{
		update_pwds(shell, old);
		shell->exit_status = 0;
	}
}

void	mis_cd(t_command *cmd, t_minishell *shell)
{
	char	*dir;
	char	old_pwd[PATH_MAX];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
		return ;
	}
	if (!getcwd(old_pwd, PATH_MAX))
		old_pwd[0] = '\0';
	dir = handle_cd_args(cmd->args[1], shell);
	if (!dir)
	{
		shell->exit_status = 1;
		return ;
	}
	perform_cd_exec(shell, dir, cmd->args[1], old_pwd);
}
