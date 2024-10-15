/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:19:54 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/15 12:28:09 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	err_rd(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	data->error = true;
}

bool	check_error_infile(char *str, t_data *data)
{
	if (!str)
		return (false);
	if (!last_chara(str, '<'))
		return (false);
	if (ft_strlen(str) == 1)
		return (err_rd("bash: syntax error near unexpected token `<'\n" \
		, data), true);	
	else if (ft_strlen(str) == 2)
		return (err_rd("bash: syntax error near unexpected token `<<'\n" \
		, data), true);	
	else if (ft_strlen(str) > 2)
		return (err_rd("bash: syntax error near unexpected token `<<<'\n" \
		, data), true);	
	return (false);
}

bool	check_error_outfile(char *str, t_data *data)
{
	if (!str)
		return (false);
	if (!last_chara(str, '>'))
		return (false);
	if (ft_strlen(str) == 1)
		return (err_rd("bash: syntax error near unexpected token `>'\n" \
		, data), true);	
	else if (ft_strlen(str) > 1)
		return (err_rd("bash: syntax error near unexpected token `>>'\n" \
		, data), true);	
	return (false);
}
