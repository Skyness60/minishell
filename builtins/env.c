/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:45:46 by sperron           #+#    #+#             */
/*   Updated: 2024/09/16 11:21:00 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_env(t_data *data, char **args, int ac, int fd)
{
	int	i;

	i = 0;
	(void)args;
	(void)ac;
	while (data->env[i])
	{
		if (data->env[i][0] != '?' && data->env[i][0] != '-')
		{
			write(fd, data->env[i], ft_strlen(data->env[i]));
			write(fd, "\n", 2);
		}
		i++;
	}
	return (0);
}
