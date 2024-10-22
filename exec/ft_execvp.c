/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:53 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/22 13:57:00 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_empty_cmd(char *str, t_data *data)
{
	if (!str[0])
	{
		printf("bash: : command not found\n");
		free_evolution(data);
		exit (127);
	}
}

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

static int	print_exec_error(char *cmd)
{
	if (access(cmd, X_OK) == -1 && access(cmd, F_OK) == 0 && is_file(cmd))
		return (printf("%s: %s: permission denied\n", MS_NAME, cmd), 126);
	else if (is_file(cmd) == 1)
		return (printf("%s: %s: No such file or directory\n", MS_NAME, cmd),\
		126);
	else
		return (printf("%s: %s: command not found\n", MS_NAME, cmd), 127);	
}

int	ft_execvp(t_data *data, t_execs *cmd)
{
	char		*paths;
	struct stat	path_stat;
	int			status;

	check_empty_cmd(cmd->cmd, data);
	if (ft_strcmp(cmd->cmd, "") != 0)
		paths = find_path(data->paths, cmd);
	if (execve(paths, cmd->args, data->env) == -1)
	{
		if ((stat(paths, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		|| (cmd->cmd[1] == '/' && access(paths, F_OK) == 0))
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
	free(paths);
	exit(0);
}
