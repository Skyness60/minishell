/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:43:45 by sperron           #+#    #+#             */
/*   Updated: 2024/09/13 15:46:02 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execvp(t_data *data, char **cmds)
{
	char	*paths;

	paths = find_path(data->paths, cmds[0]);
	if (execve(paths, cmds, data->env) == -1)
	{
		if (errno == ENOENT)
			printf("%s: %s: command not found\n", MS_NAME, cmds[0]);
		else
			printf("%s: %s: No such file or directory\n", MS_NAME, cmds[0]);
		exit(127);
	}
	exit(0);
}
