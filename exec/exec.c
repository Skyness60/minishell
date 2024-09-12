/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 16:29:50 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_data *data, char **cmds, int in_fd, int out_fd)
{
	pid_t	pid;
	int		status;
	char	*paths;

	pid = fork();
	paths = find_path(data->paths, cmds[0]);
	if (pid == 0)
	{
		if (in_fd != 0)
			return (dup2(in_fd, 0), close(in_fd));
		if (out_fd != 1)
			return (dup2(out_fd, 1), close(out_fd));
		if (ft_execvp(paths, cmds, data->env))
		{
			if (errno == ENOENT)
				printf("%s: %s: command not found\n", MS_NAME, cmds[0]);
			else
				printf("%s: %s: No such file or directory\n", MS_NAME, cmds[0]);
			exit(127);
		}
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
