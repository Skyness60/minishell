/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:57:30 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/18 16:27:41 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	check_space_tab(char **args, int i)
{
	if (!args || !args[i])
		return (1);
	while (args[i])
	{
		if (ft_isspace(args[i]) != -1)
			i++;
		else
			return (1);
	}
	return (0);
}


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
				if (args[i][1] != 'c' || args[i][1] != 'r' || \
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


int	handle_history(t_data *data, char **args, int ac, int fd)
{
	size_t	i;

	(void)ac;
	(void)fd;
	i = 1;
	if (args[1] && ft_strncmp(args[1], "-c", 2) == 0 && (args[2] == NULL \
	|| check_space_tab(args, 2) == 0))
		return (rl_clear_history(), free_history(data->history), 0);
	if (args[1] == NULL || check_space_tab(args, 1) == 0)
	{
		i = 0;
		while (i < data->history->count)
		{
			printf("%lu\t%s\n", i + 1, data->history->save[i]);
			i++;
		}
		return (0);
	}
	else if (check_options_null(args) == 1)
		return (150);
	return (170);
}