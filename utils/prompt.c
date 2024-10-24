/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:54:47 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/24 10:46:34 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define PROMPT_SIZE 1024
#define PATH_SIZE 1024

void	get_simpler_path(char *home_dir, char *path)
{
	size_t	home_dir_len;
	size_t	path_len;

	if (!home_dir || !path)
		return;
	home_dir_len = ft_strlen(home_dir);
	path_len = ft_strlen(path);
	if (home_dir_len == 0 || path_len == 0)
		return ;
	if (home_dir_len > path_len)
		return;
	if (ft_strncmp(home_dir, path, home_dir_len) == 0)
	{
		ft_memmove(path + 2, path + home_dir_len, path_len - home_dir_len + 1);
		path[0] = '~';
		path[1] = '/';
	}
}

char	*get_var_in_env(char **env, char *var, t_data *data)
{
	int		i;
	char	*dest;
	char	*var_name;

	dest = NULL;
	var_name = extract_var_name(var, data);
	if (!var_name)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0 && env[i][ft_strlen(var_name)] == '=')
		{
			dest = ft_strdup(env[i] + ft_strlen(var_name) + 1);
			break;
		}
		else if (ft_strcmp(var_name, "UID") == 0)
		{
			dest = get_uid();
			break;
		}
	}
	free(var_name);
	return (add_ptr(data->trash, dest), dest);
}

