/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:17:34 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/17 15:10:28 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ')
		(*i)++;
}

static char	*read_word(char *str, int *i)
{
	int			start;
	t_quotes	quote;

	start = *i;
	quote = NOT_IN_QUOTES;
	while (str[*i])
	{
		if (str[*i] == '\'' && quote == NOT_IN_QUOTES)
			quote = IN_SINGLE_QUOTES;
		else if (str[*i] == '\'' && quote == IN_SINGLE_QUOTES)
			quote = NOT_IN_QUOTES;
		else if (str[*i] == '"' && quote == NOT_IN_QUOTES)
			quote = IN_DOUBLE_QUOTES;
		else if (str[*i] == '"' && quote == IN_DOUBLE_QUOTES)
			quote = NOT_IN_QUOTES;
		else if (quote == NOT_IN_QUOTES
			&& (str[*i] == ' ' || str[*i] == '|'
				|| str[*i] == '<' || str[*i] == '>'))
			break ;
		(*i)++;
	}
	if (quote != NOT_IN_QUOTES)
		return (NULL);
	return (ft_substr(str, start, *i - start));
}

void	handle_angle_brackets(char *str, t_token **tokens, int *i)
{
	char	c;

	c = str[*i];
	if (str[*i + 1] == c)
	{
		if (c == '<')
			token_add_back(tokens, add_new_tok(ft_strdup("<<"), HEREDOC));
		else
			token_add_back(tokens, add_new_tok(ft_strdup(">>"), REDIR_APPEND));
		*i += 2;
	}
	else
	{
		if (c == '<')
			token_add_back(tokens, add_new_tok(ft_strdup("<"), REDIR_IN));
		else
			token_add_back(tokens, add_new_tok(ft_strdup(">"), REDIR_OUT));
		(*i)++;
	}
}

t_token	*tokenize(char *str)//not forget to delete '' ""
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		if (str[i] == '|')
		{
			token_add_back(&tokens, add_new_tok(ft_strdup("|"), PIPE));
			i++;
		}
		else if (str[i] == '<' || str[i] == '>')
			handle_angle_brackets(str, &tokens, &i);
		else
			token_add_back(&tokens, add_new_tok(read_word(str, &i), WORD));
	}
	/*// DEBUG:
	    printf("\n=== TOKENS ===\n");
    t_token *debug = tokens;
    int idx = 0;
    while (debug)
    {
        printf("[%d] type=%d value=[%s]\n", idx, debug->type, debug->value);
        debug = debug->next;
        idx++;
    }
    printf("==============\n\n");
	*/
	return (tokens);
}

// void	print_tokens(t_token *t)
// {
// 	int i = 0;
// 	while (t)
// 	{
// 		printf("token number %d    TYPE=%d VALUE=[%s]\n", i, t->type, t->value);
// 		t = t->next;
// 		i++;
// 	}
// }
//  int main ()
//  {
// print_tokens(tokenize("ec < ho >> \"hellomjhgm m >> world\" | | gr >ep |h > out"));
//  }
// // // //to compile:  cc parsing/lexer.c -I../libft -Llibft -lft