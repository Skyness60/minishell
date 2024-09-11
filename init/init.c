/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:43:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/11 08:58:04 by jlebard          ###   ########.fr       */
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
}

static char	**get_paths(char **env)
{
	int		i;
	char	*temp;
	char	**dest;

	temp = NULL;
	i = -1;
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
