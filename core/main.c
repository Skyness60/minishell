/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/12 16:41:36 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	core_loop(t_data *data)
{
	while (1)
	{
		set_input(data);
		if (ft_strncmp(data->input, "exit", 5) == 0)
			break ;
		if (data->input[0] != '\0')
		{
			parse_input(data);
		}
		else
			free(data->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.ac = argc;
	data.av = argv;
	data.trash = malloc(sizeof(t_garb_c));
	if (!data.trash)
		perror_exit("Error w/ malloc.\n", 1);
	init_garbage_collector(data.trash);
	prepare_data(&data, env);
	core_loop(&data);
	free_all(data.trash);
	free(data.trash);
	return (0);
}
