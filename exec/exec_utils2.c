/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:38:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/25 12:34:06 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_outfile(int out_fd, t_execs *cmds, int (*pipe_fd)[2], bool tab[2])
{
	close_fds_out(pipe_fd, cmds->g_data->nb_execs - 1, cmds->index - 1);
	if (cmds->outfile)
	{
		if (cmds->tronque == true)
			out_fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			out_fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_fd == -1)
			perror_exit("bash : Permission Denied", 2, cmds->g_data);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	else if (!tab[1])
	{
		dup2(pipe_fd[cmds->index - 1][1], STDOUT_FILENO);
		close(pipe_fd[cmds->index - 1][1]);
	}
	return ;
}
