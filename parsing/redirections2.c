/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:52:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/28 17:03:08 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_bis(t_data *data, t_execs *exec, int i)
{
	if (ctrl_redir_space(exec->tokens + i, data) == 0)
		return (1);
	if (exec->tokens[i][0] == '<')
		redirect_infile(data, exec, get_name_of(exec->tokens[i + 1], \
			data), (int)ft_strlen(exec->tokens[i]));
	else if (exec->tokens[i][0] == '>')
		redirect_outfile(exec, get_name_of(exec->tokens[i + 1], \
			data), data, (int)ft_strlen(exec->tokens[i]));
	return (0);
}
