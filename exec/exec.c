/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/09/10 19:30:49 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>

void	execute_cmd(t_data *data, char **cmds, int in_fd, int out_fd)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid == 0)
	{
		if (in_fd != 0)
		{
			dup2(in_fd, 0);
			close(in_fd);
		}
		if (out_fd != 1)
		{
			dup2(out_fd, 1);
			close(out_fd);
		}
		execve(cmds[0], cmds, data->env);
		// La ca marche pas, il faut utiliser execvp

		//if (execvp(data->input, cmds) == -1)
		//{
		//	perror("execvp");
		//	exit(EXIT_FAILURE);
		//}
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
