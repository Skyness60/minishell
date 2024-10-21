/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/21 01:17:09 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	print_exports(t_data *data, int fd)
{
	int	i;
	int	j;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		ft_putstr_fd("export ", fd);
		while (data->env[i][j])
		{
			ft_putchar_fd(data->env[i][j], fd);
			if (data->env[i][j] == '=')
				ft_putchar_fd('"', fd);
			if (data->env[i][j + 1] == '\0' && ft_strchr(data->env[i], '='))
				ft_putstr_fd("\"", fd);
			j++;
		}
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_exports(t_data *data, int fd)
{
	int		i;
	int		j;
	char	**env_tmp;

	i = 0;
	env_tmp = malloc((array_len(data->env) + 1) * sizeof(char *));
	if (!env_tmp)
		return ;
	if (data->env)
		ft_memcpy(env_tmp, data->env, array_len(data->env) * sizeof(char *));
	env_tmp[array_len(data->env)] = NULL;
	while (env_tmp[i])
	{
		j = i;
		while (env_tmp[++j])
		{
			if (ft_strcmp(env_tmp[i], env_tmp[j]) > 0)
				ft_swap(&env_tmp[i], &env_tmp[j]);
		}
		i++;
	}
	return (free(data->env), data->env = env_tmp, print_exports(data, fd));
}

bool	update_export(t_data *data, char *args)
{
	int	i;
	int	j;

	i = -1;
	j = ft_arglen(args);
	if (args[j] != '=')
	{
		while (data->env[++i])
		{
			if (ft_strcmp(data->env[i], args) == 0)
				return (true);
			else
			{
				j = ft_arglen(data->env[i]);
				if (ft_strncmp(data->env[i], args, j) == 0)
					return (true);
			}
		}
		return (false);
	}
	while (data->env[++i])
		if (ft_strncmp(data->env[i], args, j) == 0)
			return (free(data->env[i]), data->env[i] = ft_strdup(args), true);
	return (false);
}

int handle_export(t_data *data, char **args, int ac, int fd)
{
    int     i;

    (void)fd;
    if (ac == 1)
        return (sort_exports(data, fd), 0);
    i = 1;
    while (args[i])
    {
		if (i == 1 && args[i][0] == '-')
			return (export_error(args[i], 2, fd), 2);
		if (!is_valid_identifier(args[i]))
			return (export_error(args[i], 1, fd), 1);
		if (update_export(data, args[i]) == false)
			add_export(data, args[i]);
        i++;
    }
    return (0);
}
