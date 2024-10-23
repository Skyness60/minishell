/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:43:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/23 15:07:26 by sperron          ###   ########.fr       */
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

int get_effective_length(const char *str) {
    int len = 0;
    int in_color = 0;

    while (*str) {
        if (*str == '\033') {
            in_color = 1; // On entre dans un code de couleur
        } else if (in_color && (*str == 'm')) {
            in_color = 0; // On sort du code de couleur
        } else if (!in_color) {
            len++;
        }
        str++;
    }
    return len;
}

void set_input(t_data *data) {
	
	signal(SIGINT, ft_signal_outside);
	signal(SIGQUIT, SIG_IGN);
	init_garbage_collector(data->trash);
	data->save_infiles = NULL;
	data->input = readline("Minishell > ");
	if (g_signal.signal_status != 0 && g_signal.signal_status != 1)
		data->cmd_exit_status = g_signal.signal_status;
	reset_struct(data);
	if (!data->input)
	{
		printf("\n");
		return ;
	}

	if (data->input[0] != '\0') {
		add_history(data->input);
		prepare_history(data);
	}

	data->input = replace_var(data->input, data);
	data->cmd_exit_status = 0;

	add_ptr(data->trash, (void *)data->input);
	if (!data->input) {
		free_tab(data->env);
		exit(1);
	}

	data->paths = get_paths(data->env);
	add_ptr_tab(data->trash, (void **)data->paths, array_len(data->paths), true);
}
