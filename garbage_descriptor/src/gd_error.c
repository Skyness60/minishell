/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:50:14 by sperron           #+#    #+#             */
/*   Updated: 2024/11/08 14:30:39 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_descriptor.h"

static void	gd_putstr(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
}

void	gd_error(t_garbage_descriptor *trash_fds, t_error_gd error)
{
	if (error == REALLOC_ERROR)
		return (clear_fds(trash_fds), gd_putstr("REALLOC_ERROR\n"));
	if (error == FD_MAX_ERROR)
		return (clear_fds(trash_fds), gd_putstr("FD_MAX_ERROR\n"));
	if (error == EMPTY_TRASH_ERROR)
		return (clear_fds(trash_fds), gd_putstr("EMPTY_TRASH_ERROR\n"));
	if (error == MALLOC_ERROR)
		return (clear_fds(trash_fds), gd_putstr("MALLOC_ERROR\n"));
}
