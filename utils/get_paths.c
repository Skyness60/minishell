/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:08:25 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/06 11:04:45 by jlebard          ###   ########.fr       */
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
	dest = ft_split(temp, ":");
	return (dest);
}
