/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:21:36 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/25 19:44:24 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *res, char c)
{
	char	*tmp;

	tmp = res;
	res = ft_strjoin_char(tmp, c);
	free(tmp);
	return (res);
}

char	*append_str(char *res, char *str)
{
	char	*tmp;
	char	*new_res;

	if (!str)
		return (res);
	tmp = res;
	new_res = ft_strjoin(tmp, str);
	free(tmp);
	return (new_res);
}

int	handle_quotes(char c, t_quotes *quote)
{
	if (c == '\'' && *quote != IN_DOUBLE_QUOTES)
	{
		if (*quote == IN_SINGLE_QUOTES)
			*quote = NOT_IN_QUOTES;
		else
			*quote = IN_SINGLE_QUOTES;
		return (1);
	}
	if (c == '"' && *quote != IN_SINGLE_QUOTES)
	{
		if (*quote == IN_DOUBLE_QUOTES)
			*quote = NOT_IN_QUOTES;
		else
			*quote = IN_DOUBLE_QUOTES;
		return (1);
	}
	return (0);
}

static char	*handle_var_name(char *word, t_minishell *sh, int *i, char *res)
{
	char	*var_name;
	char	*value;

	var_name = get_name_for_var(word, i);
	if (var_name)
	{
		value = get_env_from_shell(var_name, sh);
		res = append_str(res, value);
		free(var_name);
		free(value);
	}
	return (res);
}

char	*dollar_expan(char *word, t_minishell *sh, int *i, char *res)
{
	if (word[*i + 1] == '\0')
		return (append_char(res, word[(*i)++]));
	if (word[*i + 1] == '"' || word[*i + 1] == '\'')
	{
		(*i)++;
		return (res);
	}
	(*i)++;
	if (word[*i] == '?')
		return (get_shell_status(sh, i, res));
	if (ft_isalpha(word[*i]) || word[*i] == '_')
		return (handle_var_name(word, sh, i, res));
	return (append_char(res, '$'));
}
