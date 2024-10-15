/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/10/15 12:39:04 by sperron          ###   ########.fr       */
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

bool	check_builtins_env(t_execs *cmds)
{
	if (ft_strcmp(cmds->cmd, "unset") == 0 ||
	ft_strcmp(cmds->cmd, "export") == 0 ||
	ft_strcmp(cmds->cmd, "cd") == 0)
		return (true);
	return (false);
}
