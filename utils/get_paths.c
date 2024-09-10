/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:08:25 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/10 17:06:49 by sperron          ###   ########.fr       */
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
	if (temp == NULL)
	{
		//exit + free + message d'erreur;
	}
	dest = ft_split(temp, ':');
	return (dest);
}
