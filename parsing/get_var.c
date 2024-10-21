/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:47:57 by sperron           #+#    #+#             */
/*   Updated: 2024/10/21 11:11:59 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*check_exit_code(char *token, t_data *data)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] == '?' && !is_in_quotes(token, i))
			token = handle_exit_code(token, data);
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
	env_value = get_var_in_env(data->env, dollar_value, data);
	str = replace_in_str(data, str, env_value, i);
	free(dollar_value);
	return (str);
}

char	*replace_var(char *str, t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		if (((str[i] == '$' && str[i + 1] && is_valid_character(str[i + 1])) \
		|| str[i + 1] == '?') && is_in_quotes(str, i) == 0)
		{
			j = 0;
			if (str[i + 1] != '?')
				while (ft_isalnum(str[i + ++j]) || str[i + j] == '_')
					;
			else
				j+=2;
			str = process_replace(data, i, j, str);
			i = -1;
		}
	}
	i = -1;
	// str = check_exit_code(str, data);
	return (str);
}
