/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:45:46 by sperron           #+#    #+#             */
/*   Updated: 2024/10/25 11:47:21 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_env(t_data *data, char **args, char *full_paths, int fd)
{
	if (is_fd_assigned_to_dev_null(fd) == 1)
		fd = 2;
	if (access(args[0], X_OK) == -1 && access(args[0], F_OK) == 0
		&& is_file(args[0]))
		return (free(full_paths), ft_putstr_fd("bash: ‘", fd),
			ft_putstr_fd(args[0], fd), \
			ft_putstr_fd("’: Permission denied\n", fd),
			add_ptr_tab(data->trash, (void **)args, array_len(args), true), \
			126);
	else if (is_file(args[0]) == 1)
		return (free(full_paths), ft_putstr_fd("bash: ‘", fd),
			ft_putstr_fd(args[0], fd), \
			ft_putstr_fd("’: No such file or directory\n", fd), 126);
	return (0);
}
