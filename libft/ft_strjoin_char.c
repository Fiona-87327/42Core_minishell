/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:00:49 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/01/16 17:01:07 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char *str, char c)
{
	int		len;
	char	*res;

	len = ft_strlen(str);
	res = malloc(len + 2);
	if (!res)
		return (NULL);
	ft_memcpy(res, str, len);
	res[len] = c;
	res[len + 1] = '\0';
	return (res);
}
