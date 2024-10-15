/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:43:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/15 14:50:35 by sperron          ###   ########.fr       */
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
		perror_exit("Error w/ malloc", 2);
	i = -1;
	while (env[++i])
	{
		dest[i] = ft_strdup(env[i]);
		if (!dest[i])
			perror_exit("Error w/ malloc", 2);
	}
	dest[i] = NULL;
	return (dest);
}

void	set_cmd(t_data *data)
{
	data->cmds = malloc(7 * sizeof(t_cmd));
	data->cmds[0] = (t_cmd){"echo", handle_echo};
	data->cmds[1] = (t_cmd){"cd", handle_cd};
	data->cmds[2] = (t_cmd){"pwd", handle_pwd};
	data->cmds[3] = (t_cmd){"export", handle_export};
	data->cmds[4] = (t_cmd){"unset", handle_unset};
	data->cmds[5] = (t_cmd){"env", handle_env};
	data->cmds[6] = (t_cmd){"history", handle_history};
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

void	set_input(t_data *data)
{
	signal(SIGINT, ft_signal);
	signal (SIGQUIT, SIG_IGN);
	init_garbage_collector(data->trash);
	data->prompt = create_prompt(data->env, data);
	data->save_infiles = NULL;
	if (data->prompt == NULL)
		return (free_tab(data->env), exit(1));
	data->input = readline(data->prompt);
	add_ptr(data->trash, (void *)data->input);
	if (data->input == NULL)
		return (free_tab(data->env), free(data->prompt), exit(1));
	data->paths = get_paths(data->env);
	add_ptr_tab(data->trash, (void **)data->paths, array_len(data->paths), \
	true);
	if (data->paths == NULL)
		return (free_tab(data->env), free(data->prompt), free(data->input), \
		exit(1));
	if (data->input[0] != '\0')
	{
		add_history(data->input);
		prepare_history(data);
	}
}
