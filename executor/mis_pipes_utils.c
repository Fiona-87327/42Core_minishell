/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_pipes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:27:55 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/02 12:39:42 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finalize_pipes_and_wait(int **pipes, int num_pipes,
	pid_t last_pid, t_minishell *shell)
{
	close_pipes(pipes, num_pipes);
	wait_all_children(last_pid, shell);
	free_pipes_memory(pipes, num_pipes);
}

void	exit_clean(t_minishell *shell, int code)
{
	ft_free_array(shell->env);
	free_cmds(shell->cmds);
	exit(code);
}
