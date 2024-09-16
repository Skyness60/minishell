/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/09/16 14:27:47 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_data *data, char **cmds, int in_fd, int out_fd)
{
	pid_t	pid;
	int		status;

	(void)cmds;
	status = is_builtin(data, out_fd);
	if (status != 127)
		return (status);
	pid = fork();
	if (pid == 0)
	{
		if (in_fd != 0)
			return (dup2(in_fd, 0), close(in_fd));
		if (out_fd != 1)
			return (dup2(out_fd, 1), close(out_fd));
		ft_execvp(data, cmds);
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
