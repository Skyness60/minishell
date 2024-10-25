/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:33:30 by sperron           #+#    #+#             */
/*   Updated: 2024/10/25 13:35:57 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_options(char **args)
{
	if (!args[1])
		return (2);
	if (args[1][0] == '-' && args[1][1] && (args[1][1] != '-' \
		|| (args[1][2] && args[1][2] == '-')) && !args[2])
		return (0);
	else if (args[1][0] == '-' && args[1][1] == '-' && args[1][2] && !args[2])
		return (1);
	return (2);
}

int	handle_pwd(t_data *data, char **args, bool is_child, int fd)
{
	char	*cwd;

	(void)data;
	if (is_child == true)
	{
		if (check_options(args) == 0)
			return (ft_dprintf(fd, "bash: pwd: -%c: invalid option\n", \
			args[1][1]), 2);
		else if (check_options(args) == 1)
			return (ft_dprintf(fd, "bash: pwd: --%c: invalid option\n", \
			args[1][2]), 2);
		cwd = getcwd(NULL, PATH_MAX);
		if (!cwd)
			return (ft_dprintf(fd, "pwd: error retrieving current directory: \
			getcwd: cannot array_len(args)cess parent directories: No such \
			file or directory\n"), 1);
		else
			return (ft_dprintf(fd, "%s\n", cwd), free(cwd), 0);
	}
	return (0);
}

// void	set_pwd(t_data *data)
// {
// 	char	*cwd;
// 	char	*toadd;

// 	cwd = getcwd(NULL, 4096);
// 	toadd = ft_strjoin("PWD=", cwd);
// 	free(cwd);
// 	putenv(toadd);
// 	add_ptr(data->trash, toadd);
// }
