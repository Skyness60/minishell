/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:11:01 by jlebard           #+#    #+#             */
/*   Updated: 2023/12/01 15:43:46 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*dest;

	if (n == 0 || size == 0)
		return (malloc(0));
	if (SIZE_MAX / n < size)
		return (NULL);
	dest = malloc(n * size);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, n * size);
	return (dest);
}

// int main()
// {
// 	size_t n = 65535; 
// 	size_t size = 65535;
// 	printf("%p\n", ft_calloc(2, 2));
// 	printf("vrai calloc : %p\n", calloc(2, 2));
// 	return 0;
// }
