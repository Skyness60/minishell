/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/12 11:49:43 by jlebard          ###   ########.fr       */
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

	init_garbage_collector(data.trash);
	(void)argc;
	(void)argv;
	prepare_data(&data, env);
	core_loop(&data);
	return (0);
	free_all(data.trash);
}
