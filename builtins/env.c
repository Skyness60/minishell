/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:45:46 by sperron           #+#    #+#             */
/*   Updated: 2024/10/22 11:14:00 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **shift_args(char **args)
{
    int i = 1;
    while (args[i])
    {
        args[i - 1] = args[i];
        i++;
    }
    args[i - 1] = NULL;
    return (args);
}

int check_command_access(t_data *data, char **args, int fd)
{
    char *full_paths;
	
	full_paths = ft_strjoin("/usr/bin/", args[0]);
    if (!full_paths)
        return perror_exit("Error with malloc", 1, data), 1;
    if (access(full_paths, X_OK) == 0)
        return (free(full_paths), data->pipes_to_ex[0]->cmd = args[0], \
		data->pipes_to_ex[0]->args = args, 128);
    else if (args[0][0] == '.' && args[0][1] == '/')
		return (free(full_paths), ft_putstr_fd("bash: ‘", fd), \
		ft_putstr_fd(args[0], fd), ft_putstr_fd("’: Permission denied\n", fd), \
		126);
    return (free(full_paths), ft_putstr_fd("bash: ‘", fd), \
	ft_putstr_fd(args[0], fd), ft_putstr_fd("’: No such file or directory\n", fd), \
	127);
}

void print_env(t_data *data, int fd)
{
    int i;

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

int handle_env(t_data *data, char **args, int ac, int fd)
{
    (void)ac;

    if (args[1] && ft_strcmp(args[1], "env") != 0)
    {
        args = shift_args(args);
        return (check_command_access(data, args, fd));
    }
    print_env(data, fd);
    return 0;  // Retourne 0 si tout se passe bien
}
