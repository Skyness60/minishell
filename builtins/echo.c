/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:28:24 by sperron           #+#    #+#             */
/*   Updated: 2024/09/16 15:40:36 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_echo(t_data *data, char **args, int ac, int fd)
{
	int	i;

	i = 1;
	(void)data;
	if (ac == 0)
		return (write(fd, "\n", 2), 0);
	while (args[i] && !ft_strcmp(args[i], "-n"))
		i++;
	while (i < ac - 1)
	{
		write(fd, args[i], ft_strlen(args[i]));
		write(fd, " ", 2);
		i++;
	}
	if (i != ac)
		write(fd, args[i], ft_strlen(args[i]));
	if (ft_strcmp(args[1], "-n"))
		write(fd, "\n", 2);
	return (0);
}
