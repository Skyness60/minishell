/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:54:47 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/17 16:40:55 by jlebard          ###   ########.fr       */
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

char	*get_var_in_env(char **env, char *var, t_data *data)
{
	int		i;
	char	*dest;
	char	*var_name;
	int		len;

	dest = NULL;
	len = 0;
	// Calcul de la longueur du nom de la variable (lettres, chiffres, underscores)
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	var_name = ft_substr(var, 0, len); // Extraire uniquement le nom de la variable
	if (!var_name)
		perror_exit("Error w/ malloc\n", 2, data);
	
	i = -1;
	while (env[++i])
	{
		// Comparer uniquement le nom de la variable, pas les parties supplémentaires
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			dest = ft_strdup(env[i] + len + 1); // Copie la valeur après le '='
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
	getcwd(cwd, PATH_SIZE);
	if (!user || !home_dir)
	{
		free_evolution(data);
		perror_exit("Error : not able to construct the prompt\n", 2, data);
	}
	get_simpler_path(home_dir, cwd);
	prompt = malloc(PROMPT_SIZE);
	prompt[0] = '\0';
	ft_strncat(prompt, user, ft_strlen(user));
	ft_strncat(prompt, "@minishelljonasz:", ft_strlen("@minishelljonasz:"));
	ft_strncat(prompt, cwd, ft_strlen(cwd));
	ft_strncat(prompt, "$ ", 2);
	add_ptr(data->trash, prompt);
	return (prompt);
}
