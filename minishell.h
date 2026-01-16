/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:47:15 by jiyawang          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2026/01/11 12:02:11 by mhnatovs         ###   ########.fr       */
=======
/*   Updated: 2026/01/16 17:18:42 by mhnatovs         ###   ########.fr       */
>>>>>>> Stashed changes
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

typedef struct s_command
{
	char						**args;
	char						*redir_in;
	char						*redir_out;
	int							append;
	int							pipe_out;
	struct s_command			*next;
}								t_command;

typedef struct s_minishell
{
	char						**env;
	int							exit_status;
}								t_minishell;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef enum e_quotes
{
	NOT_IN_QUOTES,
	IN_SINGLE_QUOTES,
	IN_DOUBLE_QUOTES
}	t_quotes;

void							mis_cd(t_command *cmd, t_minishell *shell);
void							mis_echo(t_command *cmd, t_minishell *shell);
void							mis_exit(t_command *cmd, t_minishell *shell);
void							mis_pwd(t_command *cmd, t_minishell *shell);
void							mis_env(t_command *cmd, t_minishell *shell);
void							mis_export(t_command *cmd, t_minishell *shell);
void							mis_unset(t_command *cmd, t_minishell *shell);
void							mis_exec(t_command *cmd, t_minishell *shell);
void							mis_signal_handler(int sig);
int								mis_check_signal_event(void);
int								ft_arraylen(char **array);
void							ft_free_array(char **array);
char							*get_var_name(char *arg);
char							*get_env_value(char **env, char *key);
void							add_to_env(t_minishell *shell, char *arg);
char							**expand_args(char **args, t_minishell *shell);
t_token							*add_new_tok(char *value, t_token_type type);
void							token_add_back(t_token **lst, t_token *new);
int								syntax_error(char *str);
int								check_syntax(t_token *t);
t_token							*tokenize(char *str);
void							expand_cmds(t_command	*cmds, t_minishell *sh);
void							free_tokens(t_token *t);
char							*get_name_for_var(char *word, int *i);
char							*expand_word(char *word, t_minishell *shell);
void							handle_angle_brackets(char *str, t_token **tokens, int *i);
void							command_add_back(t_command **lst, t_command *new);
t_command						*new_command(void);
int								add_arg_to_cmd(t_command *cmd, char *word);
t_command						*parse_tokens(t_token *t, t_minishell *sh);
char							*delete_quotes(char *str);

#endif