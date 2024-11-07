/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:53:03 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/07 10:25:07 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*force_space(char *str, int pos, t_data *data)
{
	int		i;
	int		j;
	char	*dest;
	
	i = -1;
	dest = malloc((ft_strlen(str) + 3) * sizeof(char));
	if (!dest)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, dest);
	while(++i < pos)
		dest[i] = str[i];
	dest[i++] = ' ';
	j = i;
	while (str[j] == str[i - 1])
	{
		dest[i] = str[i - 1];	
		i++;
	}
	dest[i++] = ' ';
	while (i <= (int)ft_strlen(str))
	{
		dest[i] = str[i - 2];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*split_redirs(t_data *data, char *pipe)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (pipe[++i])
	{
		if ((pipe[i] == '<' || pipe[i] == '>') && !is_in_doublequotes(pipe, i) \
			&& !is_in_quotes(pipe, i))
		{
			pipe = force_space(pipe, i, data);
			j = i;
			while (pipe[i] == pipe[j])
				i++;
			j = 0;
		}
	}
	return (pipe);
}
