/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/09/16 15:35:29 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_data *data, int fd, char **cmds)
{
	int i;
	int	len;

	len = array_len(cmds);
	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(cmds[0], data->cmds[i].name))
			return (data->cmds[i].handler(data, cmds, len, fd));
		i++;
	}
	return 127;
}
