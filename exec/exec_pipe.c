/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:34:52 by sperron           #+#    #+#             */
/*   Updated: 2024/09/10 19:29:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipes(t_data *data, char **pipes, int nb_parts)
{
	int		i;
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	char	**cmds;
	
	i = 0;
	in_fd = 0;
	while (i < nb_parts)
	{
		cmds = split_if_quote(pipes[i], ' ');
		if (!cmds)
			return ;
		if (pipe(pipe_fd) == -1)
			return ;
		if (i == nb_parts - 1)
			out_fd = 1;
		else
			out_fd = pipe_fd[1];
		execute_cmd(data, cmds, in_fd, out_fd);
		close(pipe_fd[1]);
		in_fd = pipe_fd[0];
		i++;
	}
}


