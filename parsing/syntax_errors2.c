/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:26:43 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/13 10:48:05 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ctrl_pipes(char *str)
{
	int	i;

	i = 0;	
	while (str[i])
	{
		if (str[i] == '|' && \
			!is_in_doublequotes(str, i) && !is_in_quotes(str, i))
		{
			while (str[++i] && ft_isspace(str[i]) == 1)
				;
			if (!str[i])
				return (printf("minishell: not supporting eol '|'\n"), 1);
			else if (str[i] == '|')
				return (printf \
				("bash: syntax error near unexpected token `|'\n"), 1);
		}
		i++;
	}
	return (0);
}
