/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/19 16:13:28 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// static int	export_error(char *argv, int fd)
// {
// 	write(fd, "bash: export: '", 16);
// 	write(fd, argv, ft_strlen(argv));
// 	write(fd, "' :not a valid identifier\n", 27);
// 	return (1);
// }

#include <stdlib.h>
#include <string.h>

void add_export(t_data *data, char *args)
{
    char *result;
    int env_len;
    char **env_temp;
    int j;
	int k;
	int i;
    char *args_without_value;

	j = 0;
    while (args[j] != '=' && args[j] != '\0')
        j++;
    
    args_without_value = malloc((j + 1) * sizeof(char));
    if (!args_without_value)
        return;

    i = 0;
    while (i < j)
    {
        args_without_value[i] = args[i];
        i++;
    }
    args_without_value[i] = '\0';

    if (ft_str_alnum(args_without_value) == true)
    {
        result = ft_strdup(args);
        if (!result)
        {
            free(args_without_value);
            return;
        }

        env_len = array_len(data->env);
        env_temp = malloc((env_len + 2) * sizeof(char *));
        if (!env_temp)
        {
            free(result);
            free(args_without_value);
            return;
        }

        if (data->env)
        {
            int k = 0;
            while (k < env_len)
            {
                env_temp[k] = data->env[k];
                k++;
            }
        }
        env_temp[env_len] = result;
        env_temp[env_len + 1] = NULL;

        free(data->env);
        data->env = env_temp;
    }
    
    free(args_without_value);
}

void	print_exports(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("export %s\n", data->env[i]);
		i++;
	}
}

void	sort_exports(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;
	char	**env_tmp;
	int		env_len;

	i = -1;
	env_len = array_len(data->env);
	env_tmp = malloc((env_len + 1) * sizeof(char *));
	if (!env_tmp)
		return ;
	if (data->env)
		ft_memcpy(env_tmp, data->env, env_len * sizeof(char *));
	env_tmp[env_len] = NULL;
	while (env_tmp[++i])
	{
		j = i;
		while (env_tmp[++j])
		{
			if (ft_strcmp(env_tmp[i], env_tmp[j]) > 0)
			{
				tmp = env_tmp[i];
				env_tmp[i] = env_tmp[j];
				env_tmp[j] = tmp;
			}
		}
	}
	return (free(data->env), data->env = env_tmp, print_exports(data));
}

bool	update_export(t_data *data, char *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[j] != '=' && args[j])
		j++;
	if (args[j] != '=')
	{
		while (data->env[i])
		{
			if (ft_strcmp(data->env[i], args) == 0)
				return (true);
			i++;
		}
		return (false);
	}
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], args, j) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(args);
			return (true);
		}
		i++;
	}
	return (false);
}

int handle_export(t_data *data, char **args, int ac, int fd)
{
    int     i;

    (void)fd;
    if (ac == 1)
        return (sort_exports(data), 0);
    i = 1;
    while (args[i])
    {
		if (update_export(data, args[i]) == false)
			add_export(data, args[i]);
        i++;
    }
    return (0);
}
