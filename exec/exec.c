/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:55:28 by sperron           #+#    #+#             */
/*   Updated: 2024/09/18 16:24:25 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_cmd(t_data *data, char **cmds, int in_fd, int out_fd)
{
    pid_t pid;
    int status;

    status = is_builtin(data, out_fd, cmds);
    if (status == 170)
        return (printf("%s: %s: %s: numeric argument required\n", \
		MS_NAME, cmds[0], cmds[1]), 150);
    else if (status == 150)
        return (printf("%s: %s: %s: %s", MS_NAME, cmds[0], \
		cmds[1], ERR_OPTIONS_HISTORY), 150);
	else if (status != 127)
        return (status);
    pid = fork();
    if (pid == 0)
    {
        if (in_fd != 0)
            return (dup2(in_fd, 0));
        if (out_fd != 1)
            return (dup2(out_fd, 1));
        ft_execvp(data, cmds);
        exit(1);
    }
    else
        waitpid(pid, &status, 0);
    return (0);
}
