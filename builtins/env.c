/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:45:46 by sperron           #+#    #+#             */
/*   Updated: 2024/10/23 06:18:22 by sperron          ###   ########.fr       */
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
	else if (access(full_paths, X_OK) == -1)
		return (free(full_paths), data->pipes_to_ex[0]->cmd = args[0], \
		data->pipes_to_ex[0]->args = args, \
		ft_execvp(data, data->pipes_to_ex[0]), 0);
    else if (access(args[0], X_OK) == -1 && access(args[0], F_OK) == 0 && is_file(args[0]))
		return (free(full_paths), ft_putstr_fd("bash: ‘", fd), \
		ft_putstr_fd(args[0], fd), ft_putstr_fd("’: Permission denied\n", fd), \
		add_ptr_tab(data->trash, (void **)args, array_len(args), true), 126);
	else if (is_file(args[0]) == 1)
    	return (free(full_paths), ft_putstr_fd("bash: ‘", fd), \
		ft_putstr_fd(args[0], fd), ft_putstr_fd("’: No such file or directory\n", fd), \
		126);
	else
		return (free(full_paths), ft_dprintf(fd, "bash: ‘%s’: command not found\n", args[0]),
		add_ptr_tab(data->trash, (void **)args, array_len(args), true), 127);
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

char **get_arguments_after_skip(char **args)
{
    int j = 0;
    int i = 2;

    if (args == NULL) {
        return NULL; // Vérifiez si les arguments sont nuls
    }

    char **filtered_args = malloc(sizeof(char*) * 101); // Alloue 101 pour inclure NULL
    if (filtered_args == NULL) {
        return NULL; // Vérifiez l'allocation mémoire
    }


    while (args[i] != NULL && j < 100) // Limitez à 100 éléments
    {
        // Vous pouvez ajouter ici des conditions pour filtrer les arguments
        filtered_args[j] = strdup(args[i]); // Duplication pour éviter les conflits
        if (filtered_args[j] == NULL) {
            // Gérer l'erreur de duplication
            // Libérer la mémoire déjà allouée
            for (int k = 0; k < j; k++) {
                free(filtered_args[k]);
            }
            free(filtered_args);
            return NULL;
        }
        j++;
        i++;
    }
    
    filtered_args[j] = NULL; // Terminez le tableau avec NULL

    return filtered_args; // Retournez les arguments filtrés
}

int handle_env(t_data *data, char **args, int ac, int fd)
{
	(void)ac;

    if (args[1] && ft_strcmp(args[1], "env") != 0 && ft_strcmp(args[1], "-i") != 0)
    {
        args = shift_args(args);
        return (check_command_access(data, args, fd));
    }
	else if (ft_strcmp(args[1], "-i") == 0 && args[2])
		return (args = get_arguments_after_skip(args), \
		check_command_access(data, args, fd));
    print_env(data, fd);
    return 0;  // Retourne 0 si tout se passe bien
}
