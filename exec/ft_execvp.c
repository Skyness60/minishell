/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:53 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/05 15:44:46 by sperron          ###   ########.fr       */
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

static int	print_exec_error(char *cmd, char *path, bool path_exist)
{
	struct stat	path_stat;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1 && is_file(cmd))
	{
		ft_dprintf(2, "%s: %s: Permission denied\n", MS_NAME, cmd);
		return (126);
	}
	else if (stat(cmd, &path_stat) == -1)
	{
		if (!is_file(cmd) && path && path_exist == true)
		{
			ft_dprintf(2, "%s: %s: command not found\n", MS_NAME, cmd);
			return (127);
		}
		else
		{
			ft_dprintf(2, "%s: %s: No such file or directory\n", MS_NAME, cmd);
			return (127);
		}
	}
	else if (S_ISDIR(path_stat.st_mode))
		return (ft_dprintf(2, "%s: %s: Is a directory\n", MS_NAME, cmd), 126);
	else
		return (ft_dprintf(2, "%s: %s: command not found\n", MS_NAME, cmd), \
		127);
}

int	ft_execvp(t_data *data, t_execs *cmd)
{
	char		*paths;
	int			status;
	bool		path_exist;

	check_empty_cmd(cmd->cmd, data);
	paths = NULL;
	if (ft_strcmp(cmd->cmd, "") != 0)
		paths = find_path(data->paths, cmd);
	path_exist = true;
	if (!paths)
	{
		paths = ft_strdup(cmd->cmd);
		path_exist = false;
	}
	if (execve(paths, cmd->args, data->env) == -1)
	{
		status = print_exec_error(cmd->cmd, paths, path_exist);
		free(paths);
		free_evolution(data);
		exit(status);
	}
	free(paths);
	exit(0);
	return (0);
}
