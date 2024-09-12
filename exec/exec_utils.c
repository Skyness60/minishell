/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:38:44 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 15:39:29 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**find_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	paths = ft_split("0", ' ');
	return (paths);
}

char	*find_path(char **paths, char *cmd)
{
	int		i;
	char	*road;
	char	*temp;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	while (paths[i])  
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		road = ft_strjoin(temp, cmd);
		free(temp);
		if (!road)
			return (NULL);
		if (access(road, F_OK) == 0)
			return (road);
		else
			free(road);
		i++;
	}
	return (ft_strdup("0"));
}
