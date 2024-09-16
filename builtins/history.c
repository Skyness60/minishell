/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:57:30 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/16 15:17:29 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	handle_history(t_data *data)
{
	int	i;
	
	i = -1;
	if (ft_strncmp(data->input + 7, " -c", 3) == 0)
	{
		rl_clear_history();
		free_history_entry(data->history);
		return (0);
	}
	else if (data->input + 7 == NULL)
	{
		while(++i < data->history->count)
			printf("%d\t%s\n", i + 1, data->history[i]);
		return (0);
	}
	return (127);
}
