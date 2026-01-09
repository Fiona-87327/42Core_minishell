/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 19:53:02 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/09 17:01:19 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_sorted_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

char	*get_var_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	return (name);
}

void	mis_export(t_command *cmd, t_minishell *shell)
{
	int	i;

	if (!cmd->args[1])
	{
		print_sorted_env(shell->env);
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]))
		{
			add_to_env(shell, cmd->args[i]);
		}
		else
		{
			ft_putstr_fd("bash: export: `", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		}
		i++;
	}
}
