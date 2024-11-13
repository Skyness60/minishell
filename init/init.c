/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:43:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/13 09:31:55 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**dest;

	i = -1;
	while (env[++i])
		;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		exit (1);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			dest[i] = ft_strjoin_free_s2("SHLVL=", \
			ft_itoa(ft_atoi(env[i] + 6) + 1));
		else
			dest[i] = ft_strdup(env[i]);
		if (!dest[i])
			exit (1);
	}
	dest[i] = NULL;
	return (dest);
}

void	set_cmd(t_data *data)
{
	data->cmds = malloc(8 * sizeof(t_cmd));
	data->cmds[0] = (t_cmd){"echo", handle_echo};
	data->cmds[1] = (t_cmd){"cd", handle_cd};
	data->cmds[2] = (t_cmd){"pwd", handle_pwd};
	data->cmds[3] = (t_cmd){"export", handle_export};
	data->cmds[4] = (t_cmd){"unset", handle_unset};
	data->cmds[5] = (t_cmd){"env", handle_env};
	data->cmds[6] = (t_cmd){"history", handle_history};
	data->cmds[7] = (t_cmd){"exit", handle_exit};
}

static void	prepare_history(t_data *data)
{
	size_t	size;
	size_t	capacite;

	if (data->history == NULL)
	{
		data->history = malloc(sizeof(t_history));
		data->history->count = 0;
		data->history->capacite = 2;
	}
	size = data->history->count;
	capacite = data->history->capacite;
	if (size == 0)
		data->history->save = malloc(2 * sizeof(char *));
	if (size == capacite)
	{
		data->history->save = ft_realloc(data->history->save, \
		size * sizeof(char *), 2 * size * sizeof(char *));
		data->history->capacite *= 2;
	}
	data->history->save[size] = ft_strdup(data->input);
	data->history->count++;
}

void	history_condition(t_data *data)
{
	add_history(data->input);
	prepare_history(data);
}

void	set_input(t_data *data)
{
	init_garbage_collector(data->trash);
	data->save_infiles = NULL;
	data->input = readline("\001\033[1;36m\002Minishell \001\033[1;37m\002");
	handle_signals(0, 0, data);
	if (g_signals.signal_status != 0)
		data->cmd_exit_status = g_signals.signal_status;
	reset_struct(data);
	if (!data->input)
	{
		printf("\n");
		return ;
	}
	if (data->input[0] != '\0')
		history_condition(data);
	data->input = replace_var(data->input, data);
	data->cmd_exit_status = 0;
	add_ptr(data->trash, (void *)data->input);
	if (!data->input)
	{
		free_tab(data->env);
		exit(1);
	}
	data->paths = get_paths(data->env);
	add_ptr_tab(data->trash, (void **)data->paths, \
	array_len(data->paths), true);
}
