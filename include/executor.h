/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:02:44 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/23 16:19:00 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include <sys/types.h>

typedef enum e_redirect_type	t_redirect_type;
typedef enum e_quotes			t_quotes;
typedef struct s_token			t_token;

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
	char						*redir_in;
	char						*redir_out;
	int							append;
	int							pipe_out;
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
void							mis_exec_cmd(t_command *cmd,
									t_minishell *shell);
void							mis_pipes(t_command *cmd, t_minishell *shell);
void							mis_signal_handler(int sig);
int								mis_check_signal_event(void);
void							setchild_signals(void);
void							setparent_signals(void);
void							handle_child_status(int status,
									t_minishell *shell);
int								ft_arraylen(char **array);
void							ft_free_array(char **array);
void							free_cmds(t_command *cmds);
char							*get_var_name(char *arg);
char							*get_env_value(char **env, char *key);
void							add_to_env(t_minishell *shell, char *arg);
char							**expand_args(char **args, t_minishell *shell);
void							free_pipes_memory(int **pipes, int num_pipes);
void							wait_all_children(pid_t last_pid,
									t_minishell *shell);

/* Redirections */
int								mis_redirections(t_redir *redir);
void							process_heredocs(t_command *cmds,
									t_minishell *shell);
void							execute_with_pipes(t_command *cmds);
void							execute_child_command(t_command *cmd,
									t_minishell *shell);
void							execute_command(t_command *cmd,
									t_minishell *shell);
void							handle_input(char *input, t_minishell *shell);

#endif