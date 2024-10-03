/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/10/03 14:08:48 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_data *data, int fd, t_execs *cmds)
{
	int i;
	int	len;

	len = array_len(cmds->args);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(cmds->cmd, data->cmds[i].name))
			return (data->cmds[i].handler(data, cmds->args, len, fd));
		i++;
	}
	return (127);
}
