/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sytnax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:37:03 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/15 10:40:47 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *str)
{
	write(2, "minishell: syntax error near unexpected token `", 48);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	return (1);
}

static int	is_redirection(t_token *t)
{
	if (t->type == REDIR_IN || t->type == REDIR_OUT
		|| t->type == REDIR_APPEND || t->type == HEREDOC)
		return (1);
	return (0);
}

int	check_syntax(t_token *t)
{
	t_token	*prev;

	prev = NULL;
	while (t)
	{
		if (t->type == PIPE)
		{
			if (!prev)
				return (syntax_error("|"));
			if (!t->next)
				return (syntax_error("newline"));
			if (t->next->type == PIPE)
				return (syntax_error("|"));
		}
		if (is_redirection(t))
		{
			if (!t->next)
				return (syntax_error("newline"));
			if (t->next->type != WORD)
				return (syntax_error(t->next->value));
		}
		prev = t;
		t = t->next;
	}
	return (0);
}
