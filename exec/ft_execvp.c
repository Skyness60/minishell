/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:53 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/24 15:23:20 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_empty_cmd(char *str, t_data *data)
{
	if (!str[0])
	{
		ft_dprintf(2, "bash: : command not found\n");
		free_evolution(data);
		exit (127);
	}
}

bool	is_file(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (true);
		str++;
	}
	return (false);
}

static int	print_exec_error(char *cmd, char *path)
{
	if (access(cmd, X_OK) == -1 && access(cmd, F_OK) == 0 && is_file(cmd))
		return (ft_dprintf(2, "%s: %s: permission denied\n", MS_NAME, cmd), 126);
	else if (is_file(cmd) == 1 || !path)
		return (ft_dprintf(2, "%s: %s: No such file or directory\n", MS_NAME, cmd),\
		126);
	else
		return (ft_dprintf(2, "%s: %s: command not found\n", MS_NAME, cmd), 127);	
}

int	ft_execvp(t_data *data, t_execs *cmd)
{
	char		*paths;
	struct stat	path_stat;
	int			status;

	check_empty_cmd(cmd->cmd, data);
	paths = NULL;
	if (ft_strcmp(cmd->cmd, "") != 0)
		paths = find_path(data->paths, cmd);
	if (!paths)
		return (ft_dprintf(2, "%s: %s: No such file or directory\n", MS_NAME, cmd->cmd), \
		free_evolution(data), exit(127), 0);
	if (execve(paths, cmd->args, data->env) == -1)
	{
		if (stat(paths, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			ft_dprintf(2, "%s: %s: Is a directory\n", MS_NAME, cmd->cmd);
			status = 126;	
		}
		else
			status = print_exec_error(cmd->cmd, paths);
		return (free(paths), free_evolution(data), exit(status), 0);
	}
	return (free(paths), exit(0), 0);
}
