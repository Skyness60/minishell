/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/10/15 15:59:49 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_redirect(t_data *data, t_execs *cmds, int (*pipe_fd)[2])
{
	bool	tab[2];
	
	tab[0] = (cmds->index == 1);
	tab[1] = (cmds->index == data->nb_execs);
	return (get_infile(data->in_fd, cmds, pipe_fd, tab), \
	get_outfile(data->out_fd, cmds, pipe_fd, tab));	
}

void execute_cmds(t_data *data, t_execs *cmds, int (*pipe_fd)[2])
{
	int	status;

	status = 0;
	get_redirect(data, cmds, pipe_fd);
	if (ft_strcmp(cmds->cmd, "cd") != 0)
		status = is_builtin(data, data->out_fd, cmds);
	if (status != 127)
		return (free_evolution(data), exit(status));
	ft_execvp(data, cmds);
	exit(status);
}

//bool	check_exec_paths(t_data *data, t_execs **execs)
//{
//	int	i;

//	i = -1;
//	while (++i < data->nb_execs)
//	{
//		find_path();
//	}
//	return (false);
//}

int pipeslines(t_data *data, t_execs **execs, int i)
{
    int pipe_fd[data->nb_execs - 1][2];
    pid_t pid;
    int status;

    while (++i < data->nb_execs)
    {
        if (data->nb_execs - 1 > i)
            if (pipe(pipe_fd[i]) == -1)
                perror_exit("Error w/ a pipe\n", 2);
        if (check_builtins_env(find_x_node(*execs, i)))
            status = is_builtin(data, data->out_fd, find_x_node(*execs, i));
		handle_heredoc(data, find_x_node(*execs, i));
		//if (check_exec_paths(data, execs) == true)
		//	return (1);
        pid = fork();
        if (pid == 0)
            execute_cmds(data, find_x_node(*execs, i), pipe_fd);
        else
        {
			if (i > 0)
				close(pipe_fd[i - 1][0]);
			if (i < data->nb_execs - 1)
				close(pipe_fd[i][1]);
        }
    }
    return (waitfunction(data), 0);
}
