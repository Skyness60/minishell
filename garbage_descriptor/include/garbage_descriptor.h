/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_descriptor.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:09:29 by sperron           #+#    #+#             */
/*   Updated: 2024/11/08 14:31:12 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_DESCRIPTOR_H
# define GARBAGE_DESCRIPTOR_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define FD_MAX 1024

typedef enum e_error_gd
{
	NO_ERROR,
	REALLOC_ERROR,
	FD_MAX_ERROR,
	EMPTY_TRASH_ERROR,
	MALLOC_ERROR
}			t_error_gd;

typedef struct s_garbage_descriptor
{
	int		*fds;
	size_t	capacite;
	size_t	count;
}				t_garbage_descriptor;

void	init_garbage_descriptor(t_garbage_descriptor *trash_fds);
void	*gd_realloc(void *fds, size_t old_size, size_t size);
void	add_fd(t_garbage_descriptor *trash_fds, int fd);
void	close_fd(t_garbage_descriptor *trash_fds, int fd);
void	clear_fds(t_garbage_descriptor *trash_fds);
void	debug_gd(t_garbage_descriptor *trash_fds);
void	gd_error(t_garbage_descriptor *trash_fds, t_error_gd error);
#endif