/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:15:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/17 13:16:25 by mhnatovs         ###   ########.fr       */
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