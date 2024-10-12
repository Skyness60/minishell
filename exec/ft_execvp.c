/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:43:45 by sperron           #+#    #+#             */
/*   Updated: 2024/10/10 17:47:51 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execvp(t_data *data, t_execs *cmd)
{
	char	*paths;

	if (!cmd->cmd)
		exit(0);
	paths = find_path(data->paths, cmd);
	if (execve(paths, cmd->args, data->env) == -1)
	{
		if (errno == ENOENT)
			printf("%s: %s: command not found\n", MS_NAME, cmd->cmd);
		else
			printf("%s: %s: No such file or directory\n", MS_NAME, cmd->cmd);
		exit(127);
	}
	exit(0);
}
