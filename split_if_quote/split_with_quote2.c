/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quote2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:04:30 by sperron           #+#    #+#             */
/*   Updated: 2024/09/25 14:33:31 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	valid2(char **result, char *s, int count, int i)
{
	int	j;
	int	state;

	while (result[++i])
	{
		j = 0;
		state = 0;
		while (result[i][j])
		{
			if (result[i][j] == '\'')
			{
				j++;
				while (result[i][j] && result[i][j] != '\'')
				{
					state = 0;
					if (is_separator(result[i][j], s))
						state = 1;
					j++;
				}
			}
			j++;
		}
		if (state == 0)
			remove_char_from_string(result[i], result[i], count, 0);
	}
}

void	trim_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

char	*allocate_result(char *result)
{
	size_t	len;
	char	*result_and_str;

	if (!result)
		len = 0;
	else
		len = ft_strlen(result);
	result_and_str = (char *)malloc(len + 2);
	if (result_and_str == NULL)
		exit(EXIT_FAILURE);
	result_and_str[0] = '\n';
	if (result != NULL)
	{
		ft_strcpy(result_and_str + 1, result);
		free((char *)result);
	}
	else
		result_and_str[0] = '\0';
	return (result_and_str);
}

char	*concat_result(char *result_and_str, char *str, int is_last_line)
{
	char	*new_result;
	char	*str_with_newline;

	if (str && str[0] != '\0')
	{
		if (is_last_line)
			str_with_newline = ft_strjoin(str, "");
		else
			str_with_newline = ft_strjoin(str, "\n");
		new_result = ft_strjoin(result_and_str, str_with_newline);
		free(result_and_str);
		free(str_with_newline);
	}
	else
	{
		new_result = ft_strjoin(result_and_str, str);
		free(result_and_str);
	}
	return (new_result);
}

char	*prompt_command_singlequote(char *result)
{
	char	*str;
	char	*result_and_str;

	result_and_str = allocate_result(result);
	if (!result_and_str)
		return (NULL);
	while (true)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str)
			break ;
		trim_newline(str);
		if (ft_strchr(str, '\''))
		{
			result_and_str = concat_result(result_and_str, str, 1);
			free(str);
			break ;
		}
		result_and_str = concat_result(result_and_str, str, 0);
		free(str);
	}
	return (result_and_str);
}
