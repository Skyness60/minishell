/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/21 20:41:16 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int g_exit_signal = 0;

#include "../minishell.h"

void	free_history(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->history != NULL)
	{
		while (i < data->history->count)
			free(data->history->save[i++]);
		free(data->history->save);
		free(data->history);
	}
}

static void	reset_struct(t_data *data)
{
	data->error = 0;
	data->count_here = 0;
	data->nb_execs = 0;
	if (g_exit_signal != 0)
		g_exit_signal = 0;
}

void	free_evolution(t_data *data)
{
	free_tab(data->env);
	free(data->cmds);
	free_all(data->trash);
	free(data->trash);
}

void	core_loop(t_data *data, char **env)
{
	data->env = copy_env(env);
	while (true)
	{
		reset_struct(data);
		change_signals(0);
		set_input(data);
		printf("Signal : %d\n", g_exit_signal);
		if (g_exit_signal == 130)
		{
				data->cmd_exit_status = 130;
			continue ;
		}
		if (data->input)
			parse_input(data);
		free_all(data->trash);
		destroy_herdoc();
		data->cmd_exit_status = 0;
	}
	return (free_evolution(data));
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

	(void)argv;
	(void)argc;
	data.cmd_exit_status = 0;
	data.trash = malloc(sizeof(t_garb_c));
	data.cmd_exit_status = 0;
	data.trash->ptr_arr = NULL;
	data.history = NULL;
	if (!data.trash)
	{
		write (2, "Error w/ malloc\n", 17);
		exit(1);
	}
	set_cmd(&data);
	core_loop(&data, env);
	return (0);
}
