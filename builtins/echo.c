/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:28:24 by sperron           #+#    #+#             */
/*   Updated: 2024/09/19 15:25:43 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_argument(int fd, t_data *data, char *arg)
{
	char	*env_value;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i + 1])
		{
			write(fd, &arg[i + 1], 1);
			i++;
		}
		else if (arg[i] == '$' && i == 0)
		{
			env_value = ft_getenv(data->env, arg + 1);
			if (env_value)
				write(fd, env_value, ft_strlen(env_value));
			else
				write(fd, "", 0);
			break;
		}
		else
			write(fd, &arg[i], 1);
		i++;
	}
}

static void	write_args(int fd, t_data *data, char **args, int end)
{
	int		i;

	i = 1;
	while (i < end)
	{
		if (args[i])
		{
			write_argument(fd, data, args[i]);
			if (i < end - 1)
				write(fd, " ", 1);
		}
		i++;
	}
}

int	handle_echo(t_data *data, char **args, int ac, int fd)
{
	int	i;

	i = 1;
	if (ac == 1)
	{
		write(fd, "\n", 1);
		return (0);
	}
	while (i < ac && !ft_strcmp(args[i], "-n"))
		i++;
	write_args(fd, data, args, ac);
	if (i == 1 || (ac > 1 && ft_strcmp(args[1], "-n")))
		write(fd, "\n", 1);
	return (0);
}

