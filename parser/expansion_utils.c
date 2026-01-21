/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:21:36 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/19 16:59:20 by mhnatovs         ###   ########.fr       */
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

	tmp = res;
	res = ft_strjoin(tmp, str);
	free(tmp);
	return (res);
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

char	*dollar_expan(char *word, t_minishell *sh, int *i, char *res)
{
	char	*var_name;
	char	*value;

	(*i)++;
	if (word[*i] == '?')
		return (get_shell_status(sh, i, res));
	else if (ft_isalpha(word[*i]) || word[*i] == '_')
	{
		var_name = get_name_for_var(word, i);
		if (var_name)
		{
			value = get_env_from_shell(var_name, sh);
			res = append_str(res, value);
			free(var_name);
			free(value);
		}
	}
	else
	{
		res = append_char(res, '$');
		(*i)++;
	}
	return (res);
}

char	*get_shell_status(t_minishell *sh, int *i, char *res)
{
	char	*value;

	value = ft_itoa(sh->exit_status);
	res = append_str(res, value);
	free(value);
	(*i)++;
	return (res);
}
