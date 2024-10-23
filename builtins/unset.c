/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:11:12 by sperron           #+#    #+#             */
/*   Updated: 2024/10/22 15:06:19 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_error(char *argv, int status, int fd)
{
	if (status == 0)
	{
		write(fd, "bash: unset: '", 15);
		write(fd, argv, ft_strlen(argv));
		write(fd, "' :not a valid identifier\n", 27);
	}
	else if (status == 1)
	{
		write(fd, "bash: unset: ", 14);
		write(fd, argv, 2);
		write(fd, ": invalid option\n", 18);
	}
	return (1);
}

void	unset_one(t_data *data, char *arg)
{
	int		length;
	char	**pointer;
	char	*to_free;
	int		i;

	length = ft_strlen(arg);
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], arg, length) && data->env[i][length] == '=')
		{
			pointer = &data->env[i];
			to_free = data->env[i];
			while (*pointer)
			{
				pointer[0] = pointer[1];
				pointer++;
			}
			free(to_free);
		}
		i++;
	}
}

int	is_string_and_number(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!ft_isalnum(string[i]) && string[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	handle_unset(t_data *data, char **args, int ac, int fd)
{
	int	i;
	int	out;

	(void)ac;
	(void)fd;
	i = 1;
	out = 0;
	while (args[i] != NULL)
	{
		if (args[1][0] == '-')
			out = unset_error(args[1], 1, fd);
		else if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			out = unset_error(args[i], 0, fd);
		else if (is_string_and_number(args[i]))
			out = unset_error(args[i], 0, fd);
		else
			unset_one(data, args[i]);
		i++;
	}
	return (out);
}
