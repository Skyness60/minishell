/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:43:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/08/29 15:15:15 by jlebard          ###   ########.fr       */
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
	data->input = readline(data->prompt);
	data->paths = get_paths(data->env);
}
