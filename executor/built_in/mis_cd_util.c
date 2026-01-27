/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_cd_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:45:26 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/27 13:04:31 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **env, char *key)
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

static char	*expand_home(char *arg, t_minishell *shell)
{
	char	*home;
	char	*expanded;
	size_t	len;

	home = get_env_value(shell->env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	if (!arg || ft_strcmp(arg, "~") == 0)
		return (home);
	len = ft_strlen(home) + ft_strlen(arg);
	expanded = malloc(len);
	if (!expanded)
		return (NULL);
	ft_strlcpy(expanded, home, len);
	ft_strlcat(expanded, arg + 1, len);
	return (expanded);
}

char	*handle_cd_args(char *arg, t_minishell *shell)
{
	char	*dir;

	if (!arg || (arg[0] == '~' && (arg[1] == '/' || arg[1] == '\0')))
		return (expand_home(arg, shell));
	if (arg && ft_strcmp(arg, "-") == 0)
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
