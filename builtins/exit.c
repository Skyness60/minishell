/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:32:18 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/21 13:37:25 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_digits(char *str)
{
	int	status;
	int	i;
	
	status = 0;
	i = -1;
	if (str[0] == '+' || str[0] == '-')
		str++;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("bash: exit: %s: numeric argument required\n",\
			str);
			return (2);
		}
	}
	status = ft_atoi(str);
	return (status);
}

int	handle_exit(t_data *data, char **args, int ac, int fd)
{
	int		i;
	int		status;
	
	i = -1;
	status = 0;
	(void)fd;
	if (ac > 2)
		return (printf("bash: exit: too many arguments\n"), 127);
	else if (ac == 1)
		status = 0;
	else
		status = check_digits(args[1]);
	free_evolution(data);
	exit (status % 256);
}
