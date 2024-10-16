/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:28:09 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/16 10:56:23 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	only_tokens(char *str)
{
	while (str++)
	{
		if (*str != '|' || *str != '&' || *str != '<' || *str != '>' || \
		*str != ';' || *str != '&' || ft_isspace(*str) == 0)
			return (false);
	}
	return (true);
}

static void	err_msg(char *str, char c)
{
	print()
}

bool	tokens_end_beginning(char *str, char c, char d, char e)
{
	char	*msg;
	
	if (*str == c || *str == d || *str == e)
	{
		if (*(str + 1) && *(str + 1) == e && *(str + 1) == d && *(str + 1) == c)
		{
			msg = malloc(3 * sizeof(char));
			if (!msg)
				perror_exit("Error w/ malloc\n", 2);
			msg[0] = *str;
			msg[1] = *(str + 1);
			msg[2] = '\0';
			err_msg(msg, 'n');		
		}
		else
			err_msg(NULL, *str);
		return (true);
	}
}

static bool	priorize_tokens(char *str, char c, char d, char e)
{
	if (tokens_end_beginning(str, c, d, e) == 1)
		return (true);
}

bool	syntax_error(char *str)
{
	
	if (!only_tokens(str))
		return (false);
	if (ft_strcmp(str, "<>"))
		return (printf("bash: syntax error near unexpected token `newline'"), 1);
	if (priorize_tokens(str, '|', '&', ';') == 1)
		return (true);
}
