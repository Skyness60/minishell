/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:12:41 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/20 12:12:42 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	temp;

	ptr = s;
	temp = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ptr[i] = temp;
		i++;
	}
	return (s);
}

// int main()
// {
// 	char buffer[10];
// 	int c = 8;
// 	size_t n = 10;
// 	printf("%p\n", (void *)ft_memset(buffer, c, n));
//	printf("vrai memset : %p\n", memset(buffer, c, n));
// 	return 0;
// }
