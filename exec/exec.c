/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/10/10 08:29:54 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redirect_and_builtins(int in_fd, int *out_fd, t_execs *cmds)
{
	if (cmds->infile)
	{
		in_fd = open(cmds->infile, O_RDONLY);
		if (in_fd == -1)
			perror_exit("bash : No such file or directory", 2);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		return (1);
	}
	if (cmds->outfile)
	{
		if (cmds->tronque == true)
			*out_fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			*out_fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*out_fd == -1)
			return (printf("bash : Permission Denied"), 0);
		return (1);
	}
	return (0);
}

int	get_redirect_and_exec(int in_fd, int out_fd, t_execs *cmds)
{
	if (cmds->infile)
	{
		in_fd = open(cmds->infile, O_RDONLY);
		if (in_fd == -1)
			perror_exit("bash : No such file or directory", 2);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		return (1);
	}
	if (cmds->outfile)
	{
		if (cmds->tronque == true)
			out_fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			out_fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_fd == -1)
			perror_exit("bash : Permission Denied", 2);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		return (1);
	}
	return (0);
}

int execute_cmd(t_data *data, t_execs **cmds)
{
    pid_t pid;
    int status;

	if (check_builtins(data, cmds[0]) == true)
		get_redirect_and_builtins(data->in_fd, &data->out_fd, cmds[0]);
	status = is_builtin(data, data->out_fd, cmds[0]);
    pid = fork();
    if (pid == 0)
    {
		if (status != 127)
			exit(status);
		get_redirect_and_exec(data->in_fd, data->out_fd, cmds[0]);
        ft_execvp(data, cmds[0]);
        exit(1);
    }
    else
        waitpid(pid, &status, 0);
    return (0);
}
