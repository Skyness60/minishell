/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_if_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:32:02 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/06 11:51:02 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*change_quotes_in_spaces(char *str, int nb_quotes)
{
	char	*dest;
	
	dest = malloc((int)ft_strlen(str) - nb_quotes + 1);
	if (!dest)
		//malloc_error;
	while (*str)
	{
		if (*str != '"')
			*dest++ = *str;
		*str++;
	}
	return (dest);
}

char	**split_if_quote(char *str, char c)
{
	int		i;
	int		j;
	char	*temp;
	char	**dest;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			j++;
	}
	if (j % 2 == 1)
	{
		//gérer les cas dans lesquels on a un nombre impair de quotes
	}
	temp = change_quotes_in_spaces(str, j); 
	dest = ft_split(temp, c);
	free(temp);
	return (dest);
}
