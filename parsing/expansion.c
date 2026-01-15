/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 12:01:07 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/15 10:32:51 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mis_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

static char	*get_env_from_shell(char *name, t_minishell *shell)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
		{
			return (ft_strdup(shell->env[i] + len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

static char	*expand_arg(char *arg, t_minishell *shell)
{
	if (mis_strcmp(arg, "$?") == 0)
		return (ft_itoa(shell->exit_status));
	if (arg[0] == '$' && arg[1])
		return (get_env_from_shell(arg + 1, shell));
	return (ft_strdup(arg));
}

// char *expand_word(char *word, t_minishell *shell);
// {
// }

char	**expand_args(char **args, t_minishell *shell)
{
	int		i;
	char	**ptrs;
	int		size;

	i = 0;
	size = ft_arraylen(args);
	ptrs = malloc(sizeof(char *) * (size + 1));
	if (!ptrs)
		return (NULL);
	while (args[i])
	{
		ptrs[i] = expand_arg(args[i], shell);
		i++;
	}
	ptrs[i] = NULL;
	return (ptrs);
}
