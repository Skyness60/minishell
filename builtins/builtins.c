/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/10/10 17:52:21 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_data *data, int fd, t_execs *cmds)
{
	int i;
	int	len;
	if (!cmds->cmd)
		return (127);
	if (cmds->args)
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
