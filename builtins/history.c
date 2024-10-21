/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:57:30 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/21 19:53:57 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

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

int	handle_history(t_data *data, char **args, int ac, int fd)
{
	size_t	i;

	i = 1;
	(void)ac;
	(void)fd;
	if (args[1] == NULL)
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
