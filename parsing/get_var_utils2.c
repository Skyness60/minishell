/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:42:03 by sperron           #+#    #+#             */
/*   Updated: 2024/10/24 10:43:19 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*loop_process_backslashes(char *result, char *str, int *i, int *j)
{
	int	start;
	int	count;

	start = *i;
	while (str[*i] == '\\')
		(*i)++;
	count = *i - start;
	count /= 2;
	while (count > 0)
	{
		result[(*j)++] = '\\';
		count--;
	}
	return (result);
}

int	not_event(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '!' && !ft_isspace(str[i + 1]) && !is_in_quotes(str, i))
			return (1);
		i++;
	}
	return (0);
}


char	*process_backslashes(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	(void)data;
	result = malloc(strlen(str) + 1);
	if (!result)
		return NULL;
	while (str[i])
	{
		if (str[i] == '\\')
			loop_process_backslashes(result, str, &i, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
bool	is_in_doublequotes(char *str, int pos)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < pos)
		if (str[i] == '"')
			count++;
	if (count % 2 == 1)
		return (true);
	else
		return (false);
}

bool	big_conditions(char *str, int i)
{
	if (!is_in_quotes(str, i) && str[i] == '$' && str[i + 1] && \
	(is_valid_character(str[i + 1]) || str[i + 1] == '?' || \
	(str[i + 1] == '\'' && !is_in_quotes(str, i)) || (str[i + 1] == '"' \
	&& !is_in_doublequotes(str, i))) && \
	count_backslashes_pos(str, i) % 2 == 0 )
		return (true);
	else
		return (false);
}
