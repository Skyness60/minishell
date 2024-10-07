/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/10/07 13:43:20 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_cmd(t_data *data, t_execs **cmds)
{
    pid_t pid;
    int status;

    status = is_builtin(data, 1, cmds[0]);
    //if (status == 170)
    //    return (printf("%s: %s: %s: numeric argument required\n", \
	//	MS_NAME, cmds[0], cmds[1]), 150);
    //else if (status == 150)
    //    return (printf("%s: %s: %s: %s", MS_NAME, cmds[0], \
	//	cmds[1], ERR_OPTIONS_HISTORY), 150);
	//else if (status != 127)
    //    return (status);
    pid = fork();
    if (pid == 0)
    {
		if (cmds[0]->infile)
		{
			data->in_fd = open(cmds[0]->infile, O_RDONLY);
			if (data->in_fd == -1)
				perror_exit("bash : No such file or directory", 1);
			dup2(data->in_fd, STDIN_FILENO);
			close(data->in_fd);
		}
		if (cmds[0]->outfile)
		{
			if (cmds[0]->tronque == true)
				data->out_fd = open(cmds[0]->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				data->out_fd = open(cmds[0]->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (data->out_fd == -1)
				perror_exit("bash : Permission Denied", 1);
			dup2(data->out_fd, STDOUT_FILENO);
			close(data->out_fd);
		}
        ft_execvp(data, cmds[0]);
        exit(1);
    }
    else
        waitpid(pid, &status, 0);
    return (0);
}
