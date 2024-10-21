/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:04:30 by sperron           #+#    #+#             */
/*   Updated: 2024/10/21 19:55:06 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	validpipe2(char **result, char *s, int i)
{
	int	j;
	int	state;

	while (result[++i])
	{
		j = 0;
		state = 0;
		while (result[i][j])
		{
			if (result[i][j] == '\'')
			{
				j++;
				while (result[i][j] && result[i][j] != '\'')
				{
					state = 0;
					if (is_separator(result[i][j], s))
						state = 1;
					j++;
				}
			}
			j++;
		}
	}
}

char	**validpipe1(char **result, char *s)
{
	int	i;
	int	j;
	int	counter;
	int	status_quotes;

	i = 0;
	counter = 0;
	status_quotes = 0;
	while (result[i])
	{
		j = 0;
		while (result[i][j])
		{
			if (is_quote(result[i][j], &status_quotes))
				counter++;
			j++;
		}
		i++;
	}
	return (validpipe2(result, s, -1), result);
}

char	**split_pipe(char *str, char *sep)
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
	result = validpipe1(result, " \t\f\v\n");
	if (!result)
		free(result);
	return (result);
}
