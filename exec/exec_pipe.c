/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:34:52 by sperron           #+#    #+#             */
/*   Updated: 2024/09/30 13:08:03 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_infile(char *path, char **cmds, t_ppx *ppx, char *cmd)
{
	if (path[0] == '0' && path[1] == 0 && (ft_strncmp(ppx->paths[0], "0",
				2) != 0))
	{
		ppx_error(ERR_CMD_NOT_FOUND, cmds, 0, cmd);
		free(path);
		ft_free_strs(cmds);
		ppx_del(&ppx);
		exit(127);
		return ;
	}
	if (execve(path, cmds, ppx->envp) == -1)
	{
		perror(cmds[0]);
		free(path);
		ft_free_strs(cmds);
		ppx_del(&ppx);
		exit(1);
		return ;
	}
	exit(0);
}

void	ft_exec_outfile(char *path, char **cmds, t_ppx *ppx, char *cmd)
{
	if (path[0] == '0' && path[1] == 0 && (ft_strncmp(ppx->paths[0], "0",
				2) != 0))
	{
		ppx_error(ERR_CMD_NOT_FOUND, cmds, 0, cmd);
		free(path);
		ft_free_strs(cmds);
		ppx_del(&ppx);
		exit(127);
		return ;
	}
	if (execve(path, cmds, ppx->envp) == -1)
	{
		perror(cmds[0]);
		free(path);
		ft_free_strs(cmds);
		ppx_del(&ppx);
		exit(1);
		return ;
	}
	exit(1);
}

void	exec_child_first(t_ppx *ppx, char *cmd, char *file)
{
	pid_t	pid;
	char	*path;
	char	**cmds;

	cmds = split_with_quotes(cmd, " \t\n\v\f");
	path = find_path(ppx->paths, cmds[0]);
	if (!cmds || !path)
		return (ft_free_strs(cmds), free(path), ppx_del(&ppx));
	pid = fork();
	if (pid == -1)
		return (ppx_error(5, cmds, 0, cmd), ft_free_strs(cmds), \
		free(path), ppx_del(&ppx));
	else if (pid == 0)
	{
		if (file_to_pipe(file, ppx) == 1)
			return (ft_exec_infile(path, cmds, ppx, cmd), exit(0));
		else if (access(file, F_OK) == 0 && access(file, R_OK) == -1)
			return (ft_free_strs(cmds), free(path), ppx_del(&ppx), exit(1));
		else
			return (free(path), ft_free_strs(cmds), ppx_del(&ppx), exit(0));
	}
	else
		return (ft_free_strs(cmds), free(path));
}

void	exec_child_midle(t_ppx *ppx, char *cmd)
{
	pid_t	pid;
	char	*path;
	char	**cmds;

	cmds = split_with_quotes(cmd, " \t\n\v\f");
	path = find_path(ppx->paths, cmds[0]);
	if (!cmds || !path)
		return (ft_free_strs(cmds), free(path), ppx_del(&ppx));
	pid = fork();
	if (pid == -1)
		return (ft_free_strs(cmds), free(path), ppx_del(&ppx));
	else if (pid == 0)
	{
		pipe_to_pipe(ppx->prev->pipe_fd, ppx->pipe_fd, ppx);
		return (ft_exec_infile(path, cmds, ppx, cmd));
	}
	else
		return (ft_free_strs(cmds), free(path));
}

int	execute_pipes(t_data *data, char **pipes, int nb_parts)
{
	t_ppx	*ppx;
	char	**split_cmds;
	int		i;

	i = -1;
	split_cmds = malloc(sizeof(char **) * array_len(pipes));
	if (!split_cmds)
		return (0);
	while (pipes[++i])
		split_cmds[i] = *split_with_quotes(pipes[i], " \t\n\v\f");
	printf("%s\n", split_cmds[2]);
	ppx = NULL;
	i = 4;
	if (ppx_add_back(&ppx, ppx_new(data->env)) == -1)
		return (0);
	if (pipe(ppx->pipe_fd) == -1)
		return (ppx_error(4, split_cmds, 0, 0), ppx_del(&ppx), 0);
	exec_child_first(ppx, split_cmds[1], split_cmds[0]);
	while (split_cmds[i + 1])
	{
		i = middle_cmd(&ppx, i, data->env, split_cmds);
		if (i == -1)
			return (ppx_del(&ppx), 0);
	}
	exec_child_last(ppx, split_cmds[nb_parts], split_cmds[i], false);
	return (close(ppx->pipe_fd[0]), close(ppx->pipe_fd[1]), ppx_del(&ppx), i);
}
