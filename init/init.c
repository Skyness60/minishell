/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:43:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/16 11:38:46 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static char	**copy_env(char **env)
{
	int		i;
	char	**dest;

	i = 0;
	while (env[i])
		i++;
	dest = malloc(sizeof(char *) * i);
	if (!dest)
		return (perror("Error w/ malloc"), NULL);
	i = -1;
	while (env[++i])
	{
		dest[i] = ft_strdup(env[i]);
		if (!dest[i])
		{
			free_tab(dest);
			return (perror("Error w/ malloc"), NULL);
		}
	}
	return (dest);
}

 void	set_cmd(t_data *data)
 {
 	data->cmds = malloc(6 * sizeof(t_cmd));
 	data->cmds[0] = (t_cmd){"echo", handle_echo};
 	data->cmds[1] = (t_cmd){"cd", handle_cd};
 	data->cmds[2] = (t_cmd){"pwd", handle_pwd};
 	data->cmds[3] = (t_cmd){"export", handle_export};
 	data->cmds[4] = (t_cmd){"unset", handle_unset};
 	data->cmds[5] = (t_cmd){"env", handle_env};
 }

void	prepare_data(t_data *data, char **env)
{
	signal(SIGINT, ft_signal);
	signal (SIGQUIT, SIG_IGN);
	data->env = copy_env(env);
	if (!data->env)
		exit(1);
	add_ptr_tab(data->trash, (void **)data->env, array_len(env));
	set_cmd(data);
}

void	set_input(t_data *data)
{
	data->prompt = create_prompt(data->env, data);
	if (data->prompt == NULL)
		return (free_tab(data->env), exit(1));
	data->input = readline(data->prompt);
	if (data->input == NULL)
		return (free_tab(data->env), free(data->prompt), exit(1));
	data->paths = get_paths(data->env);
	if (data->paths == NULL)
		return (free_tab(data->env), free(data->prompt), free(data->input), exit(1));
	
	data->in_fd = STDIN_FILENO;
	data->out_fd = STDOUT_FILENO;
	if (data->input[0] != '\0')
		add_history(data->input);
}
