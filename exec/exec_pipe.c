/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:34:52 by sperron           #+#    #+#             */
/*   Updated: 2024/10/11 15:09:49 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	array_execs(t_execs **execs)
{
	int	i;

	i = 0;
	while (execs[i])
		i++;
	return (i);
}

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

int	pipeslines(t_data *data, t_execs **execs)
{
	int	i;
	t_execs	*exec;

	i = array_execs(execs);
	first_child(data, execs);
	if (i > 2)
	{
		exec = find_x_node(*data->pipes_to_ex, i);
		//middle_childs(data, execs[i]);
		i--;
	}
	return (0);
}
