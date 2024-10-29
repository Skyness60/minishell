/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:32:18 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/29 09:29:16 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static long long int	ft_atoll(char	*str)
{
	int				i;
	long long int	n;
	long long int	j;

	i = 0;
	n = 0;
	j = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == 32))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			n++;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		if (j > (LLONG_MAX - (str[i] - '0')) / 10)
			return (258);
		j = j * 10 + (str[i] - 48);
		i++;
	}
	if (n == 1)
		return (-j);
	return (j);
}

static long long int	check_digits(char *str, bool display)
{
	long long int	status;
	int				i;

	status = 0;
	i = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (display)
				ft_dprintf(2, "bash: exit: %s: numeric argument required\n", \
				str);
			return (258);
		}
	}
	status = ft_atoll(str);
	if (status == 258)
		ft_dprintf(2, "bash: exit: %s: numeric argument required\n", str);
	return (status);
}

static long long int	change_in_positive(long long int status, bool child)
{
	(void)child;
	while (status < 0)
		status += 256;
	return (status);
}

int	handle_exit(t_data *data, char **args, bool is_child, int fd)
{
	long long int	status;
	bool			di;

	status = 0;
	close(fd);
	di = true;
	if (data->nb_execs == 1)
	{
		ft_dprintf(1, "exit\n");
		if (array_len(args) > 2 && args[1] && check_digits(args[1], di) != 258)
			return (ft_dprintf(2, "bash: exit: too many arguments\n"), \
			g_signals.signal_status = 1, 1);
		else if (array_len(args) > 2)
			di = false;
		if (array_len(args) == 1)
			status = 0;
		else
			status = check_digits(args[1], di);
		if (status == 258)
			status = 2;
		else if (status < 0)
			status = change_in_positive(status, is_child);
		return (free_evolution(data), exit(status % 256), 0);
	}
	return (0);
}
