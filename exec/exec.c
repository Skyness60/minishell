/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 08:04:42 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>
#include <errno.h>
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
	else
		waitpid(pid, &status, 0);
	return (0);
}
