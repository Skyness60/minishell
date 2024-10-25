/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:08:25 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/25 12:49:40 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths(char **env)
{
	int		i;
	char	**dest;
	char	*temp;

	temp = NULL;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			temp = ft_strdup(env[i]);
			break ;
		}
	}
	if (!temp)
		return (NULL);
	dest = ft_split(temp + 5, ':');
	if (!dest)
		*dest = ft_strdup("");
	free(temp);
	return (dest);
}
