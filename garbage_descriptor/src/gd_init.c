/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gd_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:23:52 by sperron           #+#    #+#             */
/*   Updated: 2024/11/08 13:54:49 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_descriptor.h"

void	init_garbage_descriptor(t_garbage_descriptor *trash_fds)
{
	trash_fds->capacite = 2;
	trash_fds->count = 0;
	trash_fds->fds = malloc(trash_fds->capacite * sizeof(int));
	if (trash_fds->fds == NULL)
		return (gd_error(trash_fds, MALLOC_ERROR));
}
