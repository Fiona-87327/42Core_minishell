/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_redirections_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:35:57 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/16 15:36:05 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_original_fds(t_saved_fd *saved)
{
	saved->stdin_backup = dup(STDIN_FILENO);
	saved->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_original_fds(t_saved_fd *saved)
{
	if (saved->stdin_backup != -1)
	{
		dup2(saved->stdin_backup, STDIN_FILENO);
		close(saved->stdin_backup);
	}
	if (saved->stdout_backup != -1)
	{
		dup2(saved->stdout_backup, STDOUT_FILENO);
		close(saved->stdout_backup);
	}
}
