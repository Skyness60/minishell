/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:36:03 by sperron           #+#    #+#             */
/*   Updated: 2024/10/25 11:40:15 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define DIR_SIZE 2046

static int	cd_error(char *arg, char *cdpath)
{
	if (cdpath)
	{
		if (chdir(ft_strjoin(cdpath, arg)) != -1)
			ft_dprintf(1, "%s%s\n", cdpath, arg);
		if (chdir(ft_strjoin(cdpath, arg)) == -1)
		{
			write(2, "bash: cd: ", 11);
			perror(arg);
			return (1);
		}
	}
	else
	{
		write(2, "bash: cd: ", 11);
		perror(arg);
		return (1);
	}
	return (0);
}

void	renew_env(t_data *data, char *name, size_t size)
{
	int		i;
	char	**tab;
	char	*temp;
	char	*directory;
	char	*cwd;

	directory = NULL;
	i = -1;
	cwd = getcwd(directory, DIR_SIZE);
	if (!cwd)
		size++;
	tab = data->env;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], name, size) == 0)
		{
			temp = tab[i];
			tab[i] = ft_strjoin(name, cwd);
			if (!tab[i])
				return (tab[i] = temp, free(temp));
			free(temp);
			break ;
		}
	}
	free(cwd);
}

char	*ft_getenv(char **env, char *name)
{
	size_t	len;

	len = ft_strlen(name);
	while (*env)
	{
		if (ft_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}

int	handle_cd_argscountone(t_data *data, char **args, int fd, char *cdpath)
{
	if (args[1][0] == '-' && !args[1][1])
		return (handle_pwd(data, (char *[]){"pwd", NULL}, 1, fd), 0);
	else if (args[1][0] == '-' && args[1][1] == '-' && !args[1][2])
		return (handle_cd(data, (char *[]){"cd", NULL}, 1, fd), 0);
	else if (args[1][0] == '-')
		return (ft_dprintf(2, "bash: cd: -%c: invalid option\n", args[1][1]), 2);
	if (data->nb_execs > 1)
		return (0);
	if (args[1][0] == '~')
		return (args[1] = get_var_in_env(data->env, "HOME", data), \
		renew_env(data, "PWD=", 4), 0);
	else if (chdir(args[1]) == -1)
		return (cd_error(args[1], cdpath));
	renew_env(data, "PWD=", 4);
	return (0);
}

int	handle_cd(t_data *data, char **args, bool is_child, int fd)
{
	char	*home;
	char	*get_cwd;
	char	*cdpath;

	home = NULL;
	(void)is_child;
	cdpath = get_var_in_env(data->env, "CDPATH", data);
	get_cwd = getcwd(home, 0);
	if (!get_cwd && args[1])
		return (ft_dprintf(2, "bash: cd: %s: No such file or directory\n", \
		args[1]), 1);
	free(get_cwd);
	renew_env(data, "OLDPWD=", 7);
	if ((array_len(args) - 1) == 0)
	{
		home = ft_getenv(data->env, "HOME");
		if (!home || !(*home))
			return (write(2, "bash: cd: HOME not set\n", 24), 1);
		if (chdir(home) == -1)
			return (cd_error(home, cdpath));
	}
	else if ((array_len(args) - 1) == 1)
		return (handle_cd_argscountone(data, args, fd, cdpath));
	return (write(fd, "bash: cd: too many arguments\n", 30), 1);
}
