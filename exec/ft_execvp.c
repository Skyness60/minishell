/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:53 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/17 10:58:47 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_file(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (true);
		str++;
	}
	return (false);
}

static bool	is_dir(char *cmd)
{
	if (*cmd != '/')
		return (false);
	while (*cmd)
	{
		if (*cmd != '/' && *cmd != '.')
			return (false);
		cmd++;
	}
	return (true);
}

static int	print_exec_error(char *cmd)
{
	if (access(cmd, F_OK) == -1 && is_file(cmd) == 1)
		return (printf("%s: %s: No such file or directory\n", MS_NAME, cmd),\
		126);
	else if (access(cmd, X_OK) == -1 && is_file(cmd) == 1)
		return (printf("%s: %s: permission denied\n", MS_NAME, cmd), 126);
	else if (errno == ENOENT)
		return (printf("%s: %s: command not found\n", MS_NAME, cmd), 127);
	else if (errno == ENOEXEC)
		return (printf("%s: %s: exec format error. Wrong architecture or \
		invalid executable format\n\n", MS_NAME, cmd), 126);
	else if (errno == E2BIG)
		return (printf("%s: %s: argument list too long\n", MS_NAME, cmd), 1);
	else
		printf("%s: %s: exec error\n", MS_NAME, cmd);
	return (1);		
}

int	ft_execvp(t_data *data, t_execs *cmd)
{
	char		*paths;
	struct stat	path_stat;
	int			status;

	if (!cmd->cmd)
		exit(127);
	if (ft_strcmp(cmd->cmd, "") != 0)
		paths = find_path(data->paths, cmd);
	if (execve(paths, cmd->args, data->env) == -1)
	{
		if ((stat(paths, &path_stat) == 0 && S_ISDIR(path_stat.st_mode) && \
		cmd->cmd[0] == '.' && cmd->cmd[1] == '/') || is_dir(cmd->cmd))
		{
			printf("%s: %s: Is a directory\n", MS_NAME, cmd->cmd);
			status = 126;	
		}
		else
			status = print_exec_error(cmd->cmd);
		free(paths);
		free_evolution(data);
		exit(status);
	}
	exit(0);
}
