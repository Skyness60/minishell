/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:54:47 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/12 16:29:12 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define PROMPT_SIZE 1024
#define PATH_SIZE 1024

void	get_simpler_path(char *home_dir, char *path)
{
	size_t	home_dir_len;
	size_t	path_len;

	home_dir_len = 0;
	path_len = 0;
	if (ft_strncmp(home_dir, path, ft_strlen(home_dir)) == 0)
	{
		home_dir_len = ft_strlen(home_dir);
		path_len = ft_strlen(path);
	}
	if (ft_strncmp(home_dir, path, path_len) == 0 || ((ft_strncmp(home_dir, path, path_len - 1) == 0) &&
		path[path_len] == '/'))
		ft_strlcpy(path, "~", 1);
	else
	{
		ft_memmove(path + 2, path + home_dir_len + 1, path_len - home_dir_len);
		path[0] = '~';
		path[1] = '/';
		path[path_len - home_dir_len + 1] = '\0';
	}
}

char	*get_var_in_env(char **env, char *var)
{
	int	i;
	
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0 &&
			env[i][ft_strlen(var) == '='])
		return (ft_strdup(env[i] + ft_strlen(var) + 1));
	}
	return (NULL);
}

static void	free_strs(char *user, char *home_dir, char *cwd)
{
	if (user)
		free(user);
	if (home_dir)
		free(home_dir);
	if (cwd)
		free(cwd);
}

char	*create_prompt(char **env, t_data *data)
{
	char	*home_dir;
	char	*user;
	char	*prompt;
	char	cwd[PATH_SIZE];

	user = get_var_in_env(env, "USER");
	if (!user)
		user = ft_strdup("user");
	home_dir = get_var_in_env(env, "HOME");
	getcwd(cwd, PATH_SIZE);
	if (!user || !home_dir)
		free_strs(user, home_dir, cwd);
	get_simpler_path(home_dir, cwd);
	prompt = malloc(PROMPT_SIZE);
	prompt[0] = '\0';
	ft_strncat(prompt, user, ft_strlen(user));
	ft_strncat(prompt, "@minishell:", ft_strlen("@minishell:"));
	ft_strncat(prompt, cwd, ft_strlen(cwd));
	ft_strncat(prompt, "$ ", 2);
	add_ptr(data->trash, prompt);
	free(user);
	return (prompt);
}
