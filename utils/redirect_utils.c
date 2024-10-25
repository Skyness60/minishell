/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:19:54 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/25 12:51:46 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_rd(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	data->error = true;
}

bool	checker_redirect_in(char *str, t_data *data, bool suite)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
			{
				if (str[i + 2] == '<')
					err_rd("bash: syntax error near unexpected token `<<<'\n"\
					, data);
				else
					err_rd("bash: syntax error near unexpected token `<<'\n"\
					, data);
			}
			else if (!suite && last_chara(str, '<'))
				err_rd("bash: syntax error near unexpected token `newline'\n", \
				data);
			else
				err_rd("bash: syntax error near unexpected token `<'\n", data);
			return (true);
		}
	}
	return (false);
}

bool	checker_redirect_out(char *str, t_data *data, bool suite)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				err_rd("bash: syntax error near unexpected token `>>'\n"\
					, data);
			else if (!suite && last_chara(str, '>'))
				err_rd("bash: syntax error near unexpected token `newline'\n"\
					, data);
			else
				err_rd("bash: syntax error near unexpected token `>'\n", data);
			return (true);
		}
	}
	return (false);
}
