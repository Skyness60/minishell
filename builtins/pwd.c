/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:33:30 by sperron           #+#    #+#             */
/*   Updated: 2024/10/09 12:51:10 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pwd(t_data *data, char **args, int ac, int fd)
{
	char	*cwd;
	int		error_temp;
	int		av_count;

	(void)data;
	(void)args;
	(void)fd;
	av_count = ac - 1;
	if (av_count == 0)
	{
		cwd = getcwd(NULL, PATH_MAX);
		if (!cwd)
		{
			error_temp = errno;
			write(2, "pwd: ", 6);
			write(2, strerror(error_temp), ft_strlen(strerror(error_temp)));
			write(2, "\n", 2);
		}
		else
			return (printf("%s\n", cwd), free(cwd), 0);
	}
	else
		write(2, "pwd: too many arguments\n", 25);
	return (0);
}

void	set_pwd()
{
	char	*cwd;
	char	*toadd;

	cwd = getcwd(NULL, 4096);
	toadd = ft_strjoin("PWD=", cwd);
	free(cwd);
	putenv(toadd);
	free(toadd);
}
