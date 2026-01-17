/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:35:42 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/17 19:35:43 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	length_inside_quotes(const char *str)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && !quote)
			quote = str[i++];
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	copy_without_quotes(char *dest, const char *src)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (src[i])
	{
		if (is_quote(src[i]) && !quote)
			quote = src[i++];
		else if (src[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
}

char	*delete_quotes(char *str)
{
	int		len;
	char	*clean_str;

	if (!str)
		return (NULL);
	len = length_inside_quotes(str);
	clean_str = malloc(sizeof(char) * (len + 1));
	if (!clean_str)
		return (NULL);
	copy_without_quotes(clean_str, str);
	return (clean_str);
}

int	check_quotes_balance(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}
