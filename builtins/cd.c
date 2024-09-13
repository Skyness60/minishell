/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:36:03 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 16:20:00 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int cd_error(char *arg)
{
	write(2, "bash: cd: ", 11);
	perror(arg);
	return (1);
}

int handle_cd(char **args, int args_count)
{
	char	*home;

	home = NULL;
	if (args_count == 0)
	{
		home = ft_getenv("HOME");
		if (!home || !(*home))
			return (write(2, "bash: cd: HOME not set\n", 24), 1);
		if(chdir(home) == -1)
			return (cd_error(home));
	}
	else if (args_count == 1)
	{
		if (chdir(args[0]) == -1)
			return (cd_error(args[0]));
	}
	else
		return (write(2, "cd: too many arguments\n", 24), 1);
	return (set_pwd(), 0);
}
