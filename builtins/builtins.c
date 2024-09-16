/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/09/16 10:52:26 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_data *data, int fd)
{
	int i = 0;

	while (i < 6)
	{
		if (!ft_strcmp(data->input, data->cmds[i].name))
			return (data->cmds[i].handler(data, data->av, data->ac, fd));
		i++;
	}
	return 127;
}
