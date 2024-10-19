/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/19 14:44:48 by sperron          ###   ########.fr       */
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

void	add_export(t_data *data, char *args)
{
	char	*result;
	int		env_len;
	char	**env_temp;
	
    env_len = array_len(data->env);
    if (ft_str_alnum(args) == false && args[0] != '=')
    {
		result = ft_strdup(args);
		if (!result)
			return ;
		env_temp = malloc((env_len + 2) * sizeof(char *));
		if (!env_temp)
            return (free(result));
		if (data->env)
			ft_memcpy(env_temp, data->env, env_len * sizeof(char *));
        env_temp[env_len] = result;
        env_temp[env_len + 1] = NULL;
        free(data->env);
        data->env = env_temp;
    }
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

int handle_export(t_data *data, char **args, int ac, int fd)
{
    int     i;

    (void)fd;
    if (ac == 1)
        return (sort_exports(data), 0);
    i = 1;
    while (args[i])
    {
		add_export(data, args[i]);
        i++;
    }
    return (0);
}
