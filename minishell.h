/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:47:15 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/05 20:06:17 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_checker
{
}						t_checker;

typedef struct s_command
{
	char				**args;
	struct s_command	*next;
}						t_command;

typedef struct s_minishell
{
	char				**env;
}						t_minishell;

void					mis_cd(t_command *cmd, t_minishell *shell);
void					mis_echo(t_command *cmd, t_minishell *shell);
void					mis_exit(t_command *cmd, t_minishell *shell);
void					mis_pwd(t_command *cmd, t_minishell *shell);
void					mis_env(t_command *cmd, t_minishell *shell);
void					mis_export(t_command *cmd, t_minishell *shell);
void					mis_unset(t_command *cmd, t_minishell *shell);
void					mis_exec(t_command *cmd, t_minishell *shell);

#endif
