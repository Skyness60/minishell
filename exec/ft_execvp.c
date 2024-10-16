/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:43:45 by sperron           #+#    #+#             */
/*   Updated: 2024/10/16 11:27:04 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execvp(t_data *data, t_execs *cmd)
{
	char		*paths;
	struct stat	path_stat;

	if (!cmd->cmd)
		exit(127);
	paths = find_path(data->paths, cmd);
	if (stat(paths, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		printf("%s: %s: Is a directory\n", MS_NAME, cmd->cmd);
		free(paths);
		free_evolution(data);
		exit(126);
	}
	if (execve(paths, cmd->args, data->env) == -1)
	{
		if (errno == ENOENT)
			printf("%s: %s: command not found\n", MS_NAME, cmd->cmd);
		else
			printf("%s: %s: No such file or directory\n", MS_NAME, cmd->cmd);
		exit(127);
	}
	exit(0);
}
