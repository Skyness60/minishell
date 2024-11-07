/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:53:03 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/07 11:19:57 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_space(char *str, int pos, t_data *data)
{
	int		i;
	char	*dest;
	int		j;

	i = -1;
	dest = malloc((ft_strlen(str) + 2) * sizeof(char));
	if (!dest)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, dest);
	while (++i < pos)
		dest[i] = str[i];
	j = i;
	dest[i++] = ' ';
	while (str[j])
		dest[i++] = str[j++];
	dest[i] = '\0';
	return (dest);
}

char	*split_redirs(t_data *data, char *input)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (input[++i])
	{
		if ((input[i] == '<' || input[i] == '>') && !is_in_doublequotes(input, \
		i) && !is_in_quotes(input, i))
		{
			input = add_space(input, i, data);
			i += 1;
			j = i;
			while (input[i] == input[j])
				i++;
			input = add_space(input, i, data);
			while (input[i] == input[j])
				i++;
			j = 0;
		}
	}
	return (input);
}
