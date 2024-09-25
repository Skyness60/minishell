/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:34:52 by sperron           #+#    #+#             */
/*   Updated: 2024/09/25 14:41:58 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_beggining(t_data *data, char **cmds, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		perror_exit("Error w/ pipe\n", 1);	
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror_exit("Error w/ dup2", 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(data, cmds, 0, 1);
}

static void	pipe_middle(t_data *data, char **cmds, int pipe_fd[2])
{
	if (dup2(data->in_fd, pipe_fd[0]) == -1)
		perror_exit("Error w/ dup2", 1);
	if (pipe(pipe_fd) == -1)
		perror_exit("Error w/ pipe\n", 1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror_exit("Error w/ dup2", 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_cmd(data, cmds, 0, 1);
}

static void	pipe_last(t_data *data, char **cmds, int pipe_fd[2])
{
	if (dup2(data->in_fd, pipe_fd[0]) == -1)
		perror_exit("Error w/ dup2", 1);
	execute_cmd(data, cmds, 0, 1);
}

static void	parent_process(int i, int nb_parts, int pipe_fd[2], int fd)
{
	if (nb_parts - i - 1 > 0)
	{
		close(pipe_fd[1]);
		fd = pipe_fd[0];
	}
}

void	execute_pipes(t_data *data, char **pipes, int nb_parts)
{
	int		i;
	int		pipe_fd[2];
	int		pid;
	char	**cmds;
	int		status;
	
	i = -1;
	while (++i < nb_parts)
	{
		cmds = split_with_quotes(pipes[i], " \t\n\v\f");
		if (!cmds)
			perror_exit("Error w/ malloc.\n", 2);
		pid = fork();
		if (pid == -1)
				perror_exit("Error w/ fork\n", 1);
		else if (pid == 0)
		{
			if (i == 0)
				pipe_beggining(data, cmds, pipe_fd);
			else if (nb_parts  - i  - 1 > 0)
				pipe_middle(data, cmds, pipe_fd);
			if (i - nb_parts == -1)
				pipe_last(data, cmds, pipe_fd);
		}
		else
			parent_process(i, nb_parts, pipe_fd, data->in_fd);
	}
	while (i-- > 0)
		wait(&status);
}
