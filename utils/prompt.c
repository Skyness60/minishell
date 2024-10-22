/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:54:47 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/22 17:18:05 by sperron          ###   ########.fr       */
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
	int		len;

	dest = NULL;
	len = 0;
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	var_name = ft_substr(var, 0, len);
	if (!var_name)
		perror_exit("Error w/ malloc\n", 2, data);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			dest = ft_strdup(env[i] + len + 1); 
			break;
		}
	}
	free(var_name);
	return (add_ptr(data->trash, dest), dest);
}


char	*create_prompt(char **env, t_data *data)
{
	char	*home_dir;
	char	*user;
	char	*prompt;
	char	cwd[PATH_SIZE];

	user = get_var_in_env(env, "USER", data);
	if (!user)
		user = ft_strdup("user");
	home_dir = get_var_in_env(env, "HOME", data);
	if (!user || !home_dir)
	{
		free_evolution(data);
		perror_exit("Error : not able to construct the prompt\n", 2, data);
	}
	prompt = malloc(PROMPT_SIZE);
	prompt[0] = '\0';
	if (getcwd(cwd, PATH_SIZE))
	{
		get_simpler_path(home_dir, cwd);
		ft_strncat(prompt, user, ft_strlen(user));
		ft_strncat(prompt, "@minishelljonasz:", ft_strlen("@minishelljonasz:"));
		ft_strncat(prompt, cwd, ft_strlen(cwd));
		ft_strncat(prompt, "$ ", 2);
	}
	else
		ft_strncat(prompt, "@minishelljonasz:", ft_strlen("@minishelljonasz:"));

	add_ptr(data->trash, prompt);
	return (prompt);
}
