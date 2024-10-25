/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:45:46 by sperron           #+#    #+#             */
/*   Updated: 2024/10/25 11:22:36 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**shift_args(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		args[i - 1] = args[i];
		i++;
	}
	args[i - 1] = NULL;
	return (args);
}

int	check_command_access(t_data *data, char **args, int fd, bool is_child)
{
	char	*full_paths;

	if (is_child == true)
	{
		full_paths = ft_strjoin("/usr/bin/", args[0]);
		if (!full_paths)
			return (perror_exit("Error with malloc", 1, data), 1);
		if (access(full_paths, X_OK) == 0)
			return (free(full_paths), data->pipes_to_ex[0]->cmd = args[0],
				data->pipes_to_ex[0]->args = args, 128);
		else if (access(full_paths, X_OK) == -1)
			return (free(full_paths), data->pipes_to_ex[0]->cmd = args[0],
				data->pipes_to_ex[0]->args = args,
				ft_execvp(data, data->pipes_to_ex[0]), 0);
		else if (error_env(data, args, full_paths, fd) == 126)
			return (126);
		if (is_fd_assigned_to_dev_null(fd) == 1)
			fd = 2;
		return (free(full_paths), \
		ft_dprintf(2, "bash: ‘%s’: command not found\n", args[0]), \
		add_ptr_tab(data->trash, (void **)args, array_len(args), true), 127);
	}
	return (0);
}

void	print_env(t_data *data, int fd)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (data->env[i][0] != '?' && data->env[i][0] != '-' &&
			ft_strchr(data->env[i], '='))
		{
			ft_putendl_fd(data->env[i], fd);
		}
		i++;
	}
}

char	**get_arguments_after_skip(char **args)
{
	int		j;
	int		i;
	char	**filtered_args;

	j = 0;
	i = 2;
	if (args == NULL)
		return (NULL);
	filtered_args = malloc(sizeof(char *) * 101);
	if (filtered_args == NULL)
		return (NULL);
	while (args[i] != NULL && j < 100)
	{
		filtered_args[j] = strdup(args[i]);
		if (filtered_args[j] == NULL)
		{
			while (j-- > 0)
				free(filtered_args[j]);
			free(filtered_args);
			return (NULL);
		}
		j++;
		i++;
	}
	return (filtered_args[j] = NULL, filtered_args);
}

int	handle_env(t_data *data, char **args, bool is_child, int fd)
{
	if (args[1] && ft_strcmp(args[1], "env") != 0 \
	&& ft_strcmp(args[1], "-i") != 0)
	{
		args = shift_args(args);
		return (check_command_access(data, args, fd, is_child));
	}
	else if (args[1] && ft_strcmp(args[1], "-i") == 0 && args[2])
		return (args = get_arguments_after_skip(args),
			check_command_access(data, args, fd, is_child));
	print_env(data, fd);
	return (0);
}
