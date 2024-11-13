/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:17:15 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/13 09:33:44 by jlebard          ###   ########.fr       */
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
	data->nb_execs = 0;
	data->count_quoted = 0;
	data->quote_id = NULL;
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
	clear_fds(data->trash_fds);
	free(data->trash_fds);
	clear_fds(data->trash_fds_null);
	free(data->trash_fds_null);
	free(data->trash);
}

void	core_loop(t_data *data, char **env)
{
	data->env = copy_env(env);
	while (true)
	{
		handle_signals(0, 0, data);
		reset_struct(data);
		set_input(data);
		init_garbage_descriptor(data->trash_fds);
		init_garbage_descriptor(data->trash_fds_null);
		if (!data->input)
		{
			ft_dprintf(1, "exit\n");
			free_evolution(data);
			exit(0);
		}
		if (data->input)
			parse_input(data);
		free_all(data->trash);
		clear_fds(data->trash_fds);
		clear_fds(data->trash_fds_null);
		destroy_heredoc();
	}
	return (free_evolution(data));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	(void)argc;
	data.other_minish = 0;
	g_signals.signal_status = 0;
	data.cmd_exit_status = 0;
	data.cmd_exit_status = 0;
	data.trash = malloc(sizeof(t_garb_c));
	if (!data.trash)
		return (write(2, "Error w/ malloc\n", 17), exit(1), 1);
	data.trash->ptr_arr = NULL;
	data.trash_fds = malloc(sizeof(t_garbage_descriptor));
	if (!data.trash_fds)
		return (write(2, "Error w/ malloc\n", 17), exit(1), 1);
	data.trash_fds->fds = NULL;
	data.trash_fds_null = malloc(sizeof(t_garbage_descriptor));
	if (!data.trash_fds_null)
		return (write(2, "Error w/ malloc\n", 17), exit(1), 1);
	data.trash_fds_null->fds = NULL;
	data.history = NULL;
	set_cmd(&data);
	core_loop(&data, env);
	return (0);
}
