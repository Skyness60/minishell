/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:43:45 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 16:30:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execvp(char *file, char **av, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = find_paths((char **)envp);
	if (paths == NULL || *paths == NULL)
	{
		errno = ENOENT;
		return (-1);
	}
	full_path = find_path(paths, (char *)file);
	if (full_path == NULL)
	{
		errno = ENOENT;
		return (-1);
	}
	execve(full_path, (char **)av, (char **)envp);
	free(full_path);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (-1);
}
