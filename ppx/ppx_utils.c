/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:24:14 by sperron           #+#    #+#             */
/*   Updated: 2024/10/10 08:46:15 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppx.h"

//void	ft_free_strs(char **strs)
//{
//	int	i;

//	i = 0;
//	if (!strs)
//		return ;
//	while (strs[i])
//	{
//		free(strs[i]);
//		strs[i] = NULL;
//		i++;
//	}
//	free(strs);
//}

int	file_to_pipe(t_data *data, t_execs *execs)
{
	if (execs->infile)
		data->in_fd = open(execs->infile, O_RDONLY);
	if (data->in_fd == -1)
		return (perror_exit("Bash : No such file or directory", 1), 0);
	dup2(data->in_fd, STDIN_FILENO);
	close(data->in_fd);
	return (1);
}

//int	pipe_to_file(char *file, t_ppx *ppx, bool heredoc)
//{
//	int	file_fd;

//	if (heredoc == true)
//		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//	else
//		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (file_fd == -1)
//		return (perror(file), close_pipe(ppx), 0);
//	dup2(ppx->pipe_fd[0], STDIN_FILENO);
//	dup2(file_fd, STDOUT_FILENO);
//	close_pipe(ppx);
//	close(file_fd);
//	return (1);
//}

//void	pipe_to_pipe(int pipe_fd_1[2], int pipe_fd_2[2], t_ppx *ppx)
//{
//	dup2(pipe_fd_1[0], STDIN_FILENO);
//	dup2(pipe_fd_2[1], STDOUT_FILENO);
//	close_pipe(ppx);
//}

//t_ppx	*last_pip(t_ppx *ppx)
//{
//	while (ppx->next)
//		ppx = ppx->next;
//	return (ppx);
//}
