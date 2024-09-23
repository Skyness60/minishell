/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quote3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:04:30 by sperron           #+#    #+#             */
/*   Updated: 2024/09/23 13:31:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	get_word_len(char *str, char *sep)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = 0;
	while (str[len])
	{
		if (is_quote(str[len]))
		{
			if (quote == 0)
				quote = str[len];
			else if (str[len] == quote)
				quote = 0;
		}
		else if (quote == 0 && is_separator(str[len], sep))
			break ;
		len++;
	}
	return (len);
}

void	count_word_spe(char *str, char *sep, int *count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && is_separator(str[i], sep))
			i++;
		if (str[i])
		{
			(*count)++;
			i += get_word_len(str + i, sep);
		}
	}
}

void	tab_str(char **result, char *str, char *sep, int *j)
{
	int		i;
	int		len;

	i = 0;
	while (str[i])
	{
		while (str[i] && is_separator(str[i], sep))
			i++;
		if (str[i])
		{
			len = get_word_len(str + i, sep);
			result[(*j)] = ft_strndup(str + i, len);
			(*j)++;
			i += len;
		}
	}
}

void	remove_char_from_string(char *read, char *write, char char_to_remove,
			int i)
{
	int	in_quotes;

	in_quotes = 0;
	while (read[i] != '\0')
	{
		if (is_quote(read[i]))
		{
			if (in_quotes)
				in_quotes = 0;
			else
				in_quotes = 1;
		}
		else
		{
			if (read[i] != char_to_remove || in_quotes)
				*write++ = read[i];
		}
		i++;
	}
	*write = '\0';
}
