/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:33:30 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 12:45:53 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_pwd(int	av_count)
{
	char	*cwd;
	int		error_temp;

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
		{
			printf("%s\n", cwd);
			free(cwd);
		}
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
	ft_putenv(toadd); //ft_putenv
	free(toadd);
}
