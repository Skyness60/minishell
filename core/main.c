/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/25 12:54:55 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_signals	g_signals;

void	free_history(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->history != NULL)
	{
		while (i < data->history->count)
		{
			free(data->history->save[i]);
			i++;
		}
		free(data->history->save);
		free(data->history);
		data->history = NULL;
	}
}

void	reset_struct(t_data *data)
{
	data->error = 0;
	data->count_here = 0;
	data->nb_here = 0;
	data->nb_execs = 0;
	data->in_fd = STDIN_FILENO;
	data->out_fd = STDOUT_FILENO;
	if (g_signals.signal_status != 0)
	{
		data->cmd_exit_status = g_signals.signal_status;
		g_signals.signal_status = 0;
	}
}

void	free_evolution(t_data *data)
{
	free_history(data);
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
		handle_signals(0, 0);
		reset_struct(data);
		set_input(data);
		if (!data->input)
			break ;
		if (data->input)
			parse_input(data);
		free_all(data->trash);
		destroy_heredoc();
	}
	return (free_evolution(data));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)argc;
	g_signals.other_minish = 0;
	g_signals.signal_status = 0;
	data.cmd_exit_status = 0;
	data.cmd_exit_status = 0;
	data.trash = malloc(sizeof(t_garb_c));
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
