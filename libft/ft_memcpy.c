/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:12:25 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/20 12:12:26 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
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

// int main()
// {
// 	unsigned char	*src[12];
// 	unsigned char	*dest[10];
// 	size_t	n = 8;
// 	printf("%p\n", ft_memcpy(dest, src, n));
//	printf("vrai memcpy%p\n", memcpy(dest, src, n));
//	return 0;
// }
