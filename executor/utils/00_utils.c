/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:15:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/25 19:01:14 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_cmds(t_command *cmds)
{
	t_command	*tmp;
	t_redir		*r_tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		ft_free_array(tmp->args);
		while (tmp->redirs)
		{
			r_tmp = tmp->redirs;
			tmp->redirs = tmp->redirs->next;
			free(r_tmp->filename);
			free(r_tmp);
		}
		free(tmp);
	}
}

void	free_paths(char **paths)
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

char	*get_shell_status(t_minishell *sh, int *i, char *res)
{
	char	*value;

	value = ft_itoa(sh->exit_status);
	res = append_str(res, value);
	free(value);
	(*i)++;
	return (res);
}
