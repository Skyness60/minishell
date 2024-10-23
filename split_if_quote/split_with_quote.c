/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:14:17 by sperron           #+#    #+#             */
/*   Updated: 2024/10/23 08:11:09 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split_with_quotes.h"

int	is_quote(char c, int *status_quotes)
{
	if (c == '\'' && *status_quotes != 2)
	{
		if (*status_quotes == 1)
			*status_quotes = 0;
		else
			*status_quotes = 1;
		return (1);
	}
	else if (c == '"' && *status_quotes != 1)
	{
		if (*status_quotes == 2)
			*status_quotes = 0;
		else
			*status_quotes = 2;
		return (1);
	}
	return (0);
}

int	is_separator(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

char	**valid(char **result, char *s, int count)
{
	int	i;
	int	j;
	int	counter;
	int	status_quotes;

	i = -1;
	counter = 0;
	status_quotes = 0;
	while (result[++i])
	{
		j = -1;
		while (result[i][++j])
		{
			if (is_quote(result[i][j], &status_quotes))
				counter++;
		}
	}
	if (status_quotes != 2 && status_quotes != 0 && i > 0)
			result[i - 1] = prompt_command_singlequote(result[i - 1]);
	else if (status_quotes != 1 && status_quotes != 0 && i > 0)
			result[i - 1] = prompt_command_doublequote(result[i - 1]);
	return (valid2(result, s, count, -1), result);
}

char	**split_with_quotes(char *str, char *sep)
{
	char	**result;
	int		count;
	int		j;

	if (!str)
		return (NULL);
	count = 0;
	count_word_spe(str, sep, &count);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	j = 0;
	tab_str(result, str, sep, &j);
	result[j] = NULL;
	result = valid(result, " \t\f\v\n", count);
	if (!result)
		free(result);
	return (result);
}
