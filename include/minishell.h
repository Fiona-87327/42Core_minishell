/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:47:15 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/23 14:31:20 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "executor.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>

extern volatile sig_atomic_t	g_signal;

typedef struct s_minishell		t_minishell;
typedef struct s_command		t_command;
typedef struct s_redir			t_redir;
typedef enum e_redirect_type	t_redirect_type;
typedef enum e_token_type		t_token_type;
typedef enum e_quotes			t_quotes;
typedef struct s_token			t_token;

#endif
