/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/18 15:51:45 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_history(t_history *history)
{
	size_t	i;

	i = -1;
	while (i < history->count)
		free(history->save[i++]);
	free(history);
}

void	core_loop(t_data *data, char **env)
{
	while (1)
	{
		set_input(data, env);
		if (ft_strncmp(data->input, "exit", 5) == 0)
			return (free_all(data->trash), free(data->trash), \
			free_history(data->history));
		if (data->input[0] != '\0')
			parse_input(data);
		free_all(data->trash);
	}
}

size_t	array_len(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr || !arr[0])
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.ac = argc;
	data.av = argv;
	data.trash = malloc(sizeof(t_garb_c));
	data.trash->ptr_arr = NULL;
	data.history = NULL;
	if (!data.trash)
		perror_exit("Error w/ malloc.\n", 1);
	set_cmd(&data);
	core_loop(&data, env);
	return (0);
}
