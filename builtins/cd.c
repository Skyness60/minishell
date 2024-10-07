/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:36:03 by sperron           #+#    #+#             */
/*   Updated: 2024/10/07 15:13:41 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int cd_error(char *arg)
{
	write(2, "bash: cd: ", 11);
	perror(arg);
	return (1);
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
	(void)data;
	args_count = ac - 1;
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
	return (set_pwd(), 0);
}
