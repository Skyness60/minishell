/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:47:57 by sperron           #+#    #+#             */
/*   Updated: 2024/10/21 01:12:24 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*check_exit_code(char *token, t_data *data)
{
	int	i;
	bool	status;

	i = 0;
	status = false;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] == '?')
			status = true;
		i++;
	}
	if (status == true)
		token = handle_exit_code(token, data);
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

static char	*replace_var(char *str, t_data *data)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && is_valid_character(str[i + 1]))
		{
			j = 0;
			while (ft_isalnum(str[i + ++j]) || str[i + j] == '_')
				;
			str = process_replace(data, i, j, str);
			i = -1;
		}
	}
	i = -1;
	count = count_exit_code(str);
	while (++i < count)
		str = check_exit_code(str, data);
	return (str);
}

void	replace_vars_in_tokens(char **tokens, t_data *data)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = replace_var(tokens[i], data);
		if (tokens[i][0] == '\0')
			tokens[i] = tokens[i + 1];
		i++;
	}
	add_ptr_tab(data->trash, (void **)tokens, (int)array_len(tokens), true);
}
