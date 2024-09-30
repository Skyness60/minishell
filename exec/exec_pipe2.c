/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:34:52 by sperron           #+#    #+#             */
/*   Updated: 2024/09/26 15:25:05 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child_midle(t_ppx *ppx, char *cmd)
{
	pid_t	pid;
	char	*path;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
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

int	middle_cmd(t_ppx **ppx, int i, char **envp, char **av)
{
	if (ppx_add_back(ppx, ppx_new(envp)) == -1)
		return (-1);
	*ppx = last_pip(*ppx);
	if (pipe((*ppx)->pipe_fd) == -1)
		return (perror("pip2"), -1);
	exec_child_midle(*ppx, av[i - 1]);
	close((*ppx)->prev->pipe_fd[0]);
	close((*ppx)->prev->pipe_fd[1]);
	i++;
	return (i);
}

void	exec_child_last(t_ppx *ppx, char *cmd, char *file, bool heredoc)
{
	pid_t	pid;
	char	*path;
	char	**cmds;

	cmds = split_with_quotes(cmd, ' ');
	path = find_path(ppx->paths, cmds[0]);
	if (!cmds || !path)
		return (ft_free_strs(cmds), free(path), ppx_del(&ppx));
	pid = fork();
	if (pid == -1)
		return (ppx_error(5, cmds, 0, cmd), ft_free_strs(cmds),
			free(path), ppx_del(&ppx));
	else if (pid == 0)
	{
		if (pipe_to_file(file, ppx, heredoc) == 1)
			return (ft_exec_outfile(path, cmds, ppx, cmd));
		else
			return (free(path), ft_free_strs(cmds), ppx_del(&ppx),
				exit(EXIT_FAILURE));
	}
	else
		return (ft_free_strs(cmds), free(path));
}
