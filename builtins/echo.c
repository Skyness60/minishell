/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:28:24 by sperron           #+#    #+#             */
/*   Updated: 2024/09/16 11:24:09 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int handle_echo(t_data *data, char **args, int ac, int fd)
{
	int		i;
	size_t	len;
	
	i = 0;
	(void)data;
	if (ac == 0)
		return (write(fd, "\n", 1));
	while (args[i] && !ft_strcmp(args[i], "-n"))
		i++;
	while (i < ac - 1)
	{
		len = ft_strlen(args[i]);
		write(fd, args[i], len);
		write(fd, " ", 1);
		i++;
	}
	if (i < ac)
		write(fd, args[i], ft_strlen(args[i]));
	if (ac > 0 && ft_strcmp(args[0], "-n"))
		write(fd, "\n", 1);
    return 0;
}

