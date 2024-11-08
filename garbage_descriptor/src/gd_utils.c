/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:30:57 by sperron           #+#    #+#             */
/*   Updated: 2024/11/08 13:51:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_descriptor.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < n && dest != src)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*gd_realloc(void *fds, size_t old_size, size_t new_size)
{
	void	*dest;

	if (new_size == 0)
		return (free(fds), NULL);
	dest = malloc(new_size);
	if (!dest)
		return (free(fds), NULL);
	if (fds)
	{
		if (old_size < new_size)
			ft_memcpy(dest, (const void *)fds, old_size);
		else
			ft_memcpy(dest, (const void *)fds, new_size);
		free(fds);
	}
	return (dest);
}
