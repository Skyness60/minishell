/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:36:03 by sperron           #+#    #+#             */
/*   Updated: 2024/10/11 10:42:03 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define DIR_SIZE 1024

static int cd_error(char *arg)
{
	write(2, "bash: cd: ", 11);
	perror(arg);
	return (1);
}
static void	renew_env(t_data *data, char *name, size_t size)
{
	int		i;
	char	**tab;
	char	*temp;
	char	*directory;

	directory = NULL;
	i = -1;
	tab = data->env;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], name, size) == 0)
		{
			temp = tab[i];
			tab[i] = ft_strjoin_free_s2(name, getcwd(directory, DIR_SIZE));
			if (!tab[i])
				perror_exit("Error w/ malloc\n", 2);
			free(temp);
			break ;
		}
	}
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

int handle_cd(t_data *data, char **args, int ac, int fd)
{
	char	*home;
	int		args_count;

	home = NULL;
	(void)fd;
	args_count = ac - 1;
	renew_env(data, "OLDPWD=", 7);
	if (args_count == 0)
	{
		home = ft_getenv(data->env, "HOME");
		if (!home || !(*home))
			return (write(2, "bash: cd: HOME not set\n", 24), 1);
		if(chdir(home) == -1)
			return (cd_error(home));
	}
	else if (args_count == 1)
	{
		if (chdir(args[1]) == -1)
			return (cd_error(args[0]));
	}
	else
		return (write(2, "cd: too many arguments\n", 24), 1);
	renew_env(data, "PWD=", 4);
	return (0);
	// return (set_pwd(data), 0);
}
