/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:55:26 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/13 10:31:30 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ctrl_token(char *str)
{
	if (*str == '|' || *str == ';' || *str == '&')
	{
		if (*(str + 1) && *(str + 1) == *str)
			printf("bash: syntax error near unexpected token `%c%c'\n", *str, \
				*str);
		else
			printf("bash: syntax error near unexpected token `%c'\n", *str);
		return (true);
	}
	return (false);
}

static bool	only_tokens(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '|' && str[i] != '&' && str[i] != '<' && str[i] != '>' \
		&& str[i] != ';' && ft_isspace(str[i]) == 0)
			return (false);
	}
	i = -1;
	return (true);
}

static void	deal_w_1st_token(char *str)
{
	int		i;
	int		j;
	char	*msg;

	i = 0;
	j = 0;
	while (str[i] == str[0] && i < 3)
		i++;
	if (str[i - 1] == '>' && i == 3)
		i--;
	while (str[i] == str[i + j] && j < 3)
		j++;
	if ((str[j - 1] == '>' || str[j - 1] == '|' || str[j - 1] == '&' || \
		str[j - 1] == ';') && j == 3)
		j--;
	msg = ft_strndup(str + i, j);
	printf("bash: syntax error near unexpected token `%s'\n", msg);
	free(msg);
}

static bool	basic_check(char *str)
{
	if (ft_strcmp(str, "<>") == 0)
		return (printf("bash: syntax error near unexpected token `newline'\n"), \
			1);
	if (ft_strncmp(str, "<>", 2) == 0)
		return (printf("bash: syntax error near unexpected token `<>'\n"), \
			1);
	if (ft_strcmp(str, "<") == 0)
		return (printf("bash: syntax error near unexpected token `newline'\n"), \
			1);
	if (ft_strcmp(str, "<<") == 0)
		return (printf("bash: syntax error near unexpected token `newline'\n"), \
			1);
	if (ft_strcmp(str, "<<<") == 0)
		return (printf("bash: syntax error near unexpected token `newline'\n"), \
			1);
	if (ft_strcmp(str, ">") == 0)
		return (printf("bash: syntax error near unexpected token `newline'\n"), \
			1);
	if (ft_strcmp(str, ">>") == 0)
		return (printf("bash: syntax error near unexpected token `newline'\n"), \
			1);
	return (0);
}

bool	syntax_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	if (str[i - 1] == '<' || str[i - 1] == '>')
		return (printf("bash: syntax error near unexpected token `newline'\n"),
			true);
	while (--i > 0)
	{
		if ((str[i] == ';' || str[i] == '&' || str[i] == ')' || str[i] == '(') \
		&& !is_in_doublequotes(str, i) && !is_in_quotes(str, i))
			return (printf("bash: syntax error near  unexpected token `%c'\n", \
			str[i]), true);
	}
	if (ctrl_token(str) == 1)
		return (true);
	if (ctrl_pipes(str) == 1)
		return (true);
	if (!only_tokens(str))
		return (false);
	if (basic_check(str) == 1)
		return (true);
	deal_w_1st_token(str);
	return (true);
}
