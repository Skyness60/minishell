/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:57:30 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/18 14:11:41 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	handle_history(t_data *data, char **args, int ac, int fd)
{
	size_t	i;

	(void)args;
	(void)ac;
	(void)fd;
	i = 0;
	if (ft_strncmp(data->input + 7, " -c", 3) == 0)
	{
		rl_clear_history();
		free_history(data->history);
		return (0);
	}
	else if (data->input + 7 == NULL)
	{
		while(i < data->history->count)
		{
			printf("%lu\t%s\n", i + 1, data->history->save[i]);
			i++;	
		}
		return (0);
	}
	return (127);
}
