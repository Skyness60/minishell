/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/10 14:19:34 by jlebard          ###   ########.fr       */
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
		else if (!data->input)
			continue ;
		else if (parse(data->input) == 1)
			exec_command(data);
		
	}
	//free;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	argv = NULL;
	argc = 0;
	prepare_data(&data, env);
	core_loop(&data);
	return (0);
}
