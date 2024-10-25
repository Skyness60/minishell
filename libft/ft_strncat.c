/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:17:19 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/25 12:37:02 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src != '\0' && n-- > 0)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
