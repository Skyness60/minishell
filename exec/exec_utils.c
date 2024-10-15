/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:38:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/15 09:30:41 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**find_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	paths = ft_split("0", ' ');
	return (paths);
}

char	*find_path(char **paths, t_execs *cmd)
{
	int		i;
	char	*road;
	char	*temp;

	i = 0;
	if (!cmd)
		return (NULL);
	if (access(cmd->cmd, F_OK) == 0)
		return (ft_strdup(cmd->cmd));
	while (paths[i])  
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		road = ft_strjoin(temp, cmd->cmd);
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

void	get_infile(int in_fd, t_execs *cmds, int (*pipe_fd)[2], bool tab[2])
{
	if (cmds->infile)
	{
		in_fd = open(cmds->infile, O_RDONLY);
		if (in_fd == -1)
			perror_exit("bash : No such file or directory", 2);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (!tab[0])
	{
		dup2(pipe_fd[cmds->index - 2][0], STDIN_FILENO);
		close (pipe_fd[cmds->index - 2][0]);
		// if (tab[1])
		// 	close (pipe_fd[cmds->index - 1][1]);
	}
	return ;
}

void	get_outfile(int out_fd, t_execs *cmds, int (*pipe_fd)[2], bool tab[2])
{
	if (cmds->outfile)
	{
		if (cmds->tronque == true)
			out_fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			out_fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_fd == -1)
			perror_exit("bash : Permission Denied", 2);
		dup2(out_fd, STDOUT_FILENO);
		close (out_fd);
	}
	else if (!tab[1])
	{
		dup2(pipe_fd[cmds->index - 1][1], STDOUT_FILENO);
		close (pipe_fd[cmds->index - 1][1]);
		// if (tab[0])
		// 	close (pipe_fd[cmds->index - 1][0]);
	}
	return ;
}
