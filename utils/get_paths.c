/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:08:25 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/16 10:56:40 by jlebard          ###   ########.fr       */
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
		
	}
	dest = ft_split(temp + 5, ':');
	free(temp);
	return (dest);
}
