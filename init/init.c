/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:43:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/08/07 16:59:25 by jlebard          ###   ########.fr       */
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

void	set_data(t_data *data)
{
	data->prompt = create_prompt(data->env);
}

void	init_data(t_data *data, char **env)
{
	signal(SIGINT, ft_signal);
	data->env = copy_env(env);
}
