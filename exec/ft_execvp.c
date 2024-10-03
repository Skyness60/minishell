/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:43:45 by sperron           #+#    #+#             */
/*   Updated: 2024/10/03 13:15:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execvp(t_data *data, t_execs *cmd)
{
	char	*paths;
	char	**exec_args;

	paths = find_path(data->paths, cmd->cmd);
	if (execve(paths, cmd->args, data->env) == -1)
	{
		if (errno == ENOENT)
			printf("%s: %s %s: command not found\n", MS_NAME, cmd->cmd);
		else
			printf("%s: %s: No such file or directory\n", MS_NAME, cmd->cmd);
		exit(127);
	}
	exit(0);
}
