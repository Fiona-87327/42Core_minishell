/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:45:31 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/09 12:19:17 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

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

void	mis_cd(t_command *cmd, t_minishell *shell)
{
	char	*dir;
	char	pwd[PATH_MAX];
	char	old_pwd[PATH_MAX];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
		return ;
	}
	if (!getcwd(old_pwd, PATH_MAX))
		old_pwd[0] = '\0';
	dir = cmd->args[1];
	if (!dir || (ft_strncmp(dir, "~", 2) == 0))
	{
		dir = get_env_value(shell->env, "HOME");
		if (!dir)
		{
			ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO);
			shell->exit_status = 1;
			return ;
		}
	}
	else if (ft_strncmp(dir, "-", 2) == 0)
	{
		dir = get_env_value(shell->env, "OLDPWD");
		if (!dir)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", STDERR_FILENO);
			shell->exit_status = 1;
			return ;
		}
		ft_putendl_fd(dir, STDOUT_FILENO);
	}
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("bash: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		shell->exit_status = 1;
	}
	else
	{
		update_pwd(shell, "OLDPWD", old_pwd);
		if (getcwd(pwd, PATH_MAX))
			update_pwd(shell, "PWD", pwd);
		shell->exit_status = 0;
	}
}
