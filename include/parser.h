/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:27:04 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/19 17:33:35 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "executor.h"

typedef struct s_minishell		t_minishell;
typedef struct s_command		t_command;
typedef struct s_redir			t_redir;
typedef enum e_redirect_type	t_redirect_type;

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

t_token							*tokenize(char *str);
t_command						*parse_tokens(t_token *t);
t_token							*add_new_tok(char *value, t_token_type type);
void							token_add_back(t_token **lst, t_token *new);
void							free_tokens(t_token *tokens);
int								syntax_error(char *str);
int								check_syntax(t_token *t);
void							expand_cmds(t_command *cmds, t_minishell *sh);
char							*get_name_for_var(char *word, int *i);
char							*expand_word(char *word, t_minishell *shell);
void							handle_angle_brackets(char *str,
									t_token **tokens, int *i);
void							command_add_back(t_command **lst,
									t_command *new);
t_command						*new_command(void);
int								add_arg_to_cmd(t_command *cmd, char *word);
char							*delete_quotes(char *str);
int								check_quotes_balance(char *str);
int								is_quote(char c);
char							*append_char(char *res, char c);
char							*append_str(char *res, char *str);
int								handle_quotes(char c, t_quotes *quote);
char							*dollar_expan(char *word, t_minishell *sh,
									int *i, char *res);
char							*get_shell_status(t_minishell *sh,
									int *i, char *res);
t_command						*new_command(void);
int								is_redir(t_token_type type);
t_redir							*add_redir_define_type(t_token_type type);
int								add_redir(t_command *cmd, t_token_type type,
									char *filename);
int								handle_redir(t_command *cmd, t_token *token);
char							*get_env_from_shell(char *name,
									t_minishell *shell);

#endif
