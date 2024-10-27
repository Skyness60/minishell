/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:19:54 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/28 00:07:01 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ctrl_redir_space(char **tab, t_data *data)
{
	if (!tab[1] || tab[1][0] == 0)
	{
		data->error = true;
		return (err_rd \
		("bash: syntax error near unexpected token `newline'\n", data), 0);
	}
	return (1);
}

bool	redirs_in_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '<' && str[i] != '>')
		;
	if (str[i] == 0 || str[i + 1] == 0)
		return (false);
	while (str[i] && (str[i] == '>' || str[i] == '<'))
		i++;
	if (!str[i] || str[i] == '<' || str[i] == '>')
		return (false);
	return (true);
}

void	err_rd(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	data->error = true;
}

bool	checker_redirect_in(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] == '<')
		;
	if (i == 0)
		return (false);
	else if (i == 4)
		return (err_rd("bash: syntax error near unexpected token `<'\n", \
		data), (false));
	else if (i == 5)
		return (err_rd("bash: syntax error near unexpected token `<<'\n", \
		data), (false));
	else if (i > 5)
		return (err_rd("bash: syntax error near unexpected token `<<<'\n", \
		data), (false));
	else if (str[i] == '>' && str[i + 1] == '>' && i != 0)
		return (err_rd("bash: syntaxx error near unexpected token `>>'\n", \
		data), (false));
	else if (str[i] == '>' && i != 0)
		return (err_rd("bash: syntaxx error near unexpected token `>'\n", \
		data), (false));
	return (true);
}

bool	checker_redirect_out(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] == '>')
		;
	if (i == 0)
		return (false);
	if (i == 3)
		return (err_rd("bash: syntax error near unexpected token `>'\n", \
		data), (false));
	else if (i > 3)
		return (err_rd("bash: syntax error near unexpected token `>>'\n", \
		data), (false));
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<' && i != 0)
		return (err_rd("bash: syntaxx error near unexpected token `<<<'\n", \
		data), (false));
	else if (str[i] == '<' && str[i + 1] == '<' && i != 0)
		return (err_rd("bash: syntaxx error near unexpected token `<<'\n", \
		data), (false));
	else if (str[i] == '<' && i != 0)
		return (err_rd("bash: syntaxx error near unexpected token `<'\n", \
		data), (false));
	return (true);
}
