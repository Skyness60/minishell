/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/10/25 10:59:54 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_data *data, int fd, t_execs *cmds, bool is_child)
{
	int	i;

	if (!cmds->cmd)
		return (128);
	i = 0;
	while (i < 8)
	{
		if (!ft_strcmp(cmds->cmd, data->cmds[i].name))
			return (data->cmds[i].handler(data, cmds->args, is_child, fd));
		i++;
	}
	return (128);
}

bool	check_builtins_env(t_execs *cmds)
{
	if (ft_strcmp(cmds->cmd, "unset") == 0
		|| ft_strcmp(cmds->cmd, "export") == 0
		|| ft_strcmp(cmds->cmd, "cd") == 0
		|| ft_strcmp(cmds->cmd, "history") == 0)
		return (true);
	if (ft_strcmp(cmds->cmd, "exit") == 0)
		return (true);
	return (false);
}
