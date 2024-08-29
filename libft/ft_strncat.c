/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:17:19 by jlebard           #+#    #+#             */
/*   Updated: 2024/08/29 13:19:57 by jlebard          ###   ########.fr       */
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
