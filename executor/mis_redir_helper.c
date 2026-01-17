/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_redir_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:55:55 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/17 13:16:02 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

t_saved_fd	save_fds(void)
{
	t_saved_fd	saved;

	saved.stdin_backup = dup(STDIN_FILENO);
	saved.stdout_backup = dup(STDOUT_FILENO);
	return (saved);
}

void	restore_fds(t_saved_fd saved)
{
	dup2(saved.stdin_backup, STDIN_FILENO);
	dup2(saved.stdout_backup, STDOUT_FILENO);
	close(saved.stdin_backup);
	close(saved.stdout_backup);
}
