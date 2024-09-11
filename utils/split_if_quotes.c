/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_if_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:32:02 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/11 09:11:50 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*change_quotes_in_spaces(char *str, int nb_quotes)
{
	char	*dest;
	int		i;
	
	i = 0;
	dest = malloc((int)ft_strlen(str) - nb_quotes + 1);
	// if (!dest)
	// 	perror_exit("Error w/ malloc.\n", 1);
	while (*str)
	{
		if (*str != '"' || nb_quotes == 0)
			dest[i++] = *str;
		if (*str == '"')
			nb_quotes--;
		str++;
	}
	dest[i] = '\0';
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
		j -= 1;
	temp = change_quotes_in_spaces(str, j); 
	dest = ft_split(temp, c);
	free(temp);
	return (dest);
}

// int main(int argc, char **argv)
// {
// 	char **arr;
// 	int		i;
	
// 	i = -1;
// 	arr = split_if_quote("je\" e", '|');
// 	while (arr[++i])
// 		printf("%s.\n", arr[i]);
// 	return (0);
// }
