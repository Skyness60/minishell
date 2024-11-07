/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:57:30 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/07 08:53:08 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_options_null(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '-' && j == 0)
			{
				if (args[i][1] != 'r' || \
				args[i][1] != 'a' || args[i][1] != 'w' \
				|| args[i][1] != 'd')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	handle_history(t_data *data, char **args, bool is_child, int fd)
{
	size_t	i;
	char	*nb;

	i = 1;
	(void)is_child;
	if (args[1] && ft_strncmp(args[1], "-c", 2) == 0 && \
	args[2] == NULL)
		return (rl_clear_history(), free_history(data), 0);
	if (args[1] == NULL && is_child == true)
	{
		i = -1;
		while (++i < data->history->count)
		{
			nb = ft_itoa(i + 1);
			write(fd, nb, ft_strlen(nb));
			write(fd, "\t", 2);
			ft_putstr_fd(data->history->save[i], fd);
			write(fd, "\n", 1);
			free(nb);
		}
		return (0);
	}
	else if (check_options_null(args) == 1)
		return (150);
	return (170);
}
