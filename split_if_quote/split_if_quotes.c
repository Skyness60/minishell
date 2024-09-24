/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_if_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:10:05 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/24 14:52:57 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*delete_spaces(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\n' || str[i] == '\t' || str[i] == '\v' || \
			str[i] == '\f')
			j++;
	}
	temp = malloc(sizeof(char) * (ft_strlen(str) - j + 1));
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != '\n' && str[i] != '\t' && str[i] != '\v' && \
			str[i] != '\f')
			temp[j++] = str[i];
	}
	temp[j] = '\0';
	return (temp);
}

static char	*change_quotes_in_spaces(char *str, int nb_quotes)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc((int)ft_strlen(str) - nb_quotes + 1);
	if (!dest)
		perror_exit("Error w/ malloc.\n", 1);
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

char	**split_if_quote(char *str, char *c)
{
	int		i;
	int		j;
	char	*temp;
	char	*temp2;
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
	temp2 = delete_spaces(temp);
	dest = ft_split2(temp2, c);
	free(temp);
	free(temp2);
	return (dest);
}

// static void	free_arr(char **tab)
// {
// 	int	i;

// 	i = -1;
// 	while (tab[++i])
// 		free(tab[i]);
// 	free(tab);	
// }

// int main(int argc, char **argv)
// {
// 	char **arr;
// 	int		i;
// 	i = -1;
// 	arr = split_if_quote("je\" | e", '|');
// 	while (arr[++i])
// 		printf("%s.\n", arr[i]);
// 	free_arr(arr);
// 	return (0);
// }
