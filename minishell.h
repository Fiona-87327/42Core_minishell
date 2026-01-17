/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:47:15 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/17 19:01:28 by jiyawang         ###   ########.fr       */
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

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}								t_token_type;

typedef enum e_quotes
{
	NOT_IN_QUOTES,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES
}								t_quotes;

typedef struct s_token
{
	char						*value;
	t_token_type				type;
	struct s_token				*next;
}								t_token;

typedef struct s_checker
{
}								t_checker;

typedef struct s_saved_fd
{
	int							stdin_backup;
	int							stdout_backup;
}								t_saved_fd;

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
void							mis_exec_cmd(t_command *cmd,
									t_minishell *shell);
void							mis_pipes(t_command *cmd, t_minishell *shell);
void							signal_handler(int sig);
int								check_signal_event(void);
int								ft_arraylen(char **array);
void							ft_free_array(char **array);
void							free_cmds(t_command *cmds);
char							*get_var_name(char *arg);
char							*get_env_value(char **env, char *key);
void							add_to_env(t_minishell *shell, char *arg);
char							**expand_args(char **args, t_minishell *shell);
void							execute_child_command(t_command *cmd,
									t_minishell *shell);

/* Parsing */
t_token							*tokenize(char *str);
t_command						*parse_tokens(t_token *t);
t_token							*add_new_tok(char *value, t_token_type type);
void							token_add_back(t_token **lst, t_token *new);
void							free_tokens(t_token *tokens);

/* Redirections */
int								mis_redirections(t_redir *redir);
void							process_heredocs(t_command *cmds);
void							execute_with_pipes(t_command *cmds);
t_saved_fd						save_fds(void);
void							restore_fds(t_saved_fd saved);

#endif
