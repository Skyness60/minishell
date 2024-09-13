/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:43:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/12 12:46:52 by jlebard          ###   ########.fr       */
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

void	prepare_data(t_data *data, char **env)
{	
	signal(SIGINT, ft_signal);
	signal (SIGQUIT, SIG_IGN);
	data->env = copy_env(env);
	add_ptr_tab(data->trash, data->env);
}

static char	**get_paths(char **env)
{
	int		i;
	char	*temp;
	char	**dest;

	temp = NULL;
	i = -1;
	temp = NULL;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			temp = ft_strdup(env[i] + 5);
			if (!temp)
				return (NULL);
			break ;
		}
	}
	if (!temp)
		return (NULL);
	dest = ft_split(temp, ':');
	free(temp);
	return (dest);
}

void	set_cmd(t_data *data)
{
	data->cmds = malloc(7 * sizeof(t_cmd));
	data->cmds[0] = (t_cmd){"echo", handle_echo};
	data->cmds[1] = (t_cmd){"cd", handle_cd};
	data->cmds[2] = (t_cmd){"pwd", handle_pwd};
	data->cmds[3] = (t_cmd){"export", handle_expot};
	data->cmds[4] = (t_cmd){"unset", handle_unset};
	data->cmds[5] = (t_cmd){"env", handle_env};
	data->cmds[6] = (t_cmd){"exit", handle_exit};
}

void	set_input(t_data *data)
{
	data->prompt = create_prompt(data->env);
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
