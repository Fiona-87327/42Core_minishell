/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:47:15 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/16 13:53:43 by jiyawang         ###   ########.fr       */
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

extern volatile sig_atomic_t	g_signal;

typedef struct s_checker
{
}								t_checker;

typedef struct s_saved_fd
{
	int stdin_backup;
	int stdout_backup;
}t_saved_fd;

typedef enum e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC
}								t_redirect_type;

typedef struct s_redir
{
	int							heredoc_fd;
	t_redirect_type				type;
	char						*filename;
	struct s_redir				*next;
}								t_redir;

typedef struct s_command
{
	char						**args;
	struct s_command			*next;
	t_redir						*redirs;
}								t_command;

typedef struct s_minishell
{
	char						**env;
	int							exit_status;
}								t_minishell;

void							mis_cd(t_command *cmd, t_minishell *shell);
void							mis_echo(t_command *cmd, t_minishell *shell);
void							mis_exit(t_command *cmd, t_minishell *shell);
void							mis_pwd(t_command *cmd, t_minishell *shell);
void							mis_env(t_command *cmd, t_minishell *shell);
void							mis_export(t_command *cmd, t_minishell *shell);
void							mis_unset(t_command *cmd, t_minishell *shell);
void							mis_exec(t_command *cmd, t_minishell *shell);
void							signal_handler(int sig);
int								check_signal_event(void);
int								ft_arraylen(char **array);
void							ft_free_array(char **array);
char							*get_var_name(char *arg);
char							*get_env_value(char **env, char *key);
void							add_to_env(t_minishell *shell, char *arg);
char							**expand_args(char **args, t_minishell *shell);

#endif
