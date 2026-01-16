#include "minishell.h"

char	*delete_quotes(char *str)
{
	int		i;
	int		j;
	char	*clean_str;
	char	quote;

	if (!str)
		return (NULL);
	clean_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!clean_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
		{
			quote = str[i];
			i++;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
		{
			clean_str[j++] = str[i];
			i++;
		}
	}
	clean_str[j] = '\0';
	return (clean_str);
}
