/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:28:24 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 12:46:10 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_echo(char **av, int ac, int fd)
{
	int	i;

	i = 0;
	if (ac == 0)
		return (write(fd, "\n", 2), 0);
	while (av[i] && !ft_strcmp(av[i], "-n"))
		i++;
	while (i < ac - 1)
	{
		write(fd, av[i++], ft_strlen(av[i]));
		write(fd, " ", 2);
	}
	if (i != ac)
		write(fd, av[i], ft_strlen(av[i]));
	if (ft_strcmp(av[0], "-n"))
		write(fd, "\n", 2);
	return (0);
}
