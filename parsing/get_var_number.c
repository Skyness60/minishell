/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:05:20 by sperron           #+#    #+#             */
/*   Updated: 2024/11/05 09:49:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	what_is_the_quote(char *str, int i)
{
	int	count;

	count = 0;
	if (is_in_doublequotes(str, i) && !is_in_quotes(str, i))
		return (true);
	else if (is_in_quotes(str, i) && !is_in_doublequotes(str, i))
		return (false);
	else if (is_in_doublequotes(str, i) && is_in_quotes(str, i))
	{
		i = -1;
		while (str[++i])
		{
			if (str[i] == '\"')
				return (true);
			else if (str[i] == '\'')
				return (false);
		}
	}
	return (true);
}

bool	big_conditions_number(char *str, int i)
{
	if (str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1]) && \
		count_backslashes_pos(str, i) % 2 == 0 && what_is_the_quote(str, i))
		return (true);
	else
		return (false);
}

static char	*delete_dollars(t_data *data, char *str, int size_d, int k)
{
	int		i;
	int		j;
	char	*dest;

	j = -1;
	dest = malloc((k + ft_strlen(str + k + size_d) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < k)
	{
		dest[i] = str[i];
		i++;
	}
	j = i;
	while (str[i + size_d])
		dest[j++] = str[i++ + size_d];
	dest[j] = '\0';
	add_ptr(data->trash, dest);
	return (dest);
}

char	*replace_get_var_number(t_data *data, char *str, int i)
{
	int		size_d;
	char	*dest;
	int		j;
	int		k;

	size_d = 1;
	k = -1;
	if (str[i + 1] != '0')
		return (delete_dollars(data, str, size_d + 1, i));
	dest = malloc(i + ft_strlen("bash") + ft_strlen(str + i + 2) + 1);
	if (!dest)
		return (NULL);
	j = -1;
	while (++j < i)
		dest[++k] = str[j];
	j = -1;
	while ("bash"[++j])
		dest[++k] = "bash"[j];
	j = i + 2;
	while (str[j])
		dest[++k] = str[j++];
	dest[k + 1] = '\0';
	add_ptr(data->trash, dest);
	return (dest);
}

char	*get_var_number(t_data *data, char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (big_conditions_number(str, i))
		{
			str = replace_get_var_number(data, str, i);
		}
	}
	return (str);
}
