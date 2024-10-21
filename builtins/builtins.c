/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/10/21 13:08:11 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_data *data, int fd, t_execs *cmds)
{
	int i;
	int	len;
	if (!cmds->cmd)
		return (128);
	if (cmds->args)
		len = array_len(cmds->args);
	i = 0;
	while (i < 8)
	{
		if (!ft_strcmp(cmds->cmd, data->cmds[i].name))
			return (data->cmds[i].handler(data, cmds->args, len, fd));
		i++;
	}
	return (128);
}

bool	check_builtins_env(t_execs *cmds)
{
	if (ft_strcmp(cmds->cmd, "unset") == 0 ||
	ft_strcmp(cmds->cmd, "export") == 0 ||
	ft_strcmp(cmds->cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmds->cmd, "exit") == 0 && cmds->index == 1)
		return (true);
	return (false);
}
