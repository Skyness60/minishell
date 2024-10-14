/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:34:52 by sperron           #+#    #+#             */
/*   Updated: 2024/10/14 13:13:13 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//int	pp(t_data *data, t_execs **execs)
//{
	
//}

int	first_child(t_data *data, t_execs **execs)
{
    pid_t pid;
    int status;

	if (check_builtins(data, execs[0]) == true)
		get_redirect_and_builtins(data->in_fd, &data->out_fd, execs[0]);
	status = is_builtin(data, data->out_fd, execs[0]);
    pid = fork();
    if (pid == 0)
    {
		if (status != 127)
			exit(status);
		get_redirect_and_exec(data->in_fd, data->out_fd, execs[0]);
        ft_execvp(data, execs[0]);
        exit(1);
    }
    else
	    return (0);
}

//int	middle_childs()
//{
	
//}

// 3 fonctions 
// fonction child
// fonction finale

static void	execute_several_cmds(t_data *data, t_execs *exec, int pipe_fd[2])
{
    pid_t pid;
    int status;

	if (check_builtins(data, *cmds) == true)
		get_redirect_and_builtins(data->in_fd, &data->out_fd, *cmds);
    status = is_builtin(data, data->out_fd, *cmds);
    pid = fork();
    if (pid == 0)
    {
		if (status != 127)
		{
			status = is_builtin(data->out_fdm *cmds)
			exit(status);
		}
		get_redirect_and_exec(data->in_fd, data->out_fd, *cmds, pipe_fd);
        ft_execvp(data, *cmds);
        exit(1);
    }
    else
        waitpid(pid, &status, 0);
    return (0);
}	

int	pipeslines(t_data *data, t_execs **execs)
{
	size_t	i;
	size_t	j;
	int		pipe_fd[2];
	pid_t	pid;

	j = -1;
	i = size_struct(*execs);
	first_child(data, find_x_node(*execs, 0));
	pipe(pipe_fd);
	{
		pid = fork();
		if (pid == 0)
		{
			get_redirect_and_exec(data->in_fd, data->out_fd, \
				find_x_node(*execs, j));
			exec = find_x_node(*execs, i);
			
		}
	}
	//execute (find_x_node(*execs, ++j));
	// while (++j < i - 1)
		//execute (find_x_node(*execs, j));
	//execute_last(find_x_ndoe(*execs, i - 1))
	//middle_childs(data, execs[i]);
	return (0);
}

// wkj | sleep 3 | sleep 4 |  dhuidi
// 3 structures
// size_struct == 4
// execute(find_x_node(*execs, 0) == wkj)
// while (i < 4 - 1)
// execur (find_x_node(*execs, 1) == dhsuid)
// execur (find_x_node(*execs, 1) == dfsafsafsafas)
// execute(dhuid)
