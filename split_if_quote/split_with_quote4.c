/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quote4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:04:30 by sperron           #+#    #+#             */
/*   Updated: 2024/10/16 09:54:29 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt_command_doublequote(char *result)
{
	char	*str;
	char	*result_and_str;

	result_and_str = allocate_result(result);
	if (!result_and_str)
		return (NULL);
	while (true)
	{
		str = readline("> ");
		if (!str)
			break ;
		trim_newline(str);
		if (ft_strchr(str, '"'))
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
