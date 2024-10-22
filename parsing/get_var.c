/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:47:57 by sperron           #+#    #+#             */
/*   Updated: 2024/10/22 08:39:07 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

int count_backslashes_pos(char *str, int pos)
{
    int count = 0;
    while (pos > 0 && str[--pos] == '\\')
        count++;
    return count;
}

char	*check_exit_code(char *token, t_data *data)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] == '?' && !is_in_quotes(token, i))
		{
			token = handle_exit_code(token, i, data);
			break ;
		}
		i++;
	}
	return (token);
}

int	count_exit_code(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			count++;
		i++;
	}
	return (count);
}

char	*process_replace(t_data *data, int i, int j, char *str)
{
	char	*dollar_value;
	char	*env_value;

	dollar_value = ft_substr(str, i + 1, j - 1);
	if (!ft_strchr(dollar_value, '?'))
	{
		env_value = get_var_in_env(data->env, dollar_value, data);
		str = replace_in_str(data, str, env_value, i);
	}
	else
		str = check_exit_code(str, data);
	free(dollar_value);
	if (str[0] != '\0')
		add_ptr(data->trash, str);
	return (str);
}

char	*replace_var(char *str, t_data *data)
{	
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (!is_in_quotes(str, i) && str[i] == '$' && str[i + 1] && \
		(is_valid_character(str[i + 1]) || str[i + 1] == '?') && \
		count_backslashes_pos(str, i) % 2 == 0)
		{
			j = 1;
			if (str[i + 1] != '?')
				while (is_valid_character(str[i + j]))
					j++;
			else
				j++;
			str = process_replace(data, i, j, str);
			i = -1;
		}
		if (str[i] == '$')
			continue ;
	}
	str = process_backslashes(data, str);
	return (str);
}
