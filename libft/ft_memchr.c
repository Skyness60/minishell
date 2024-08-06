/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:12:10 by jlebard           #+#    #+#             */
/*   Updated: 2023/12/01 15:46:20 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void	*s, int c, size_t n)
{
	char	*temp;

	temp = (char *)s;
	while (temp && n > 0)
	{
		if ((unsigned char)*temp == (unsigned char)c)
			return (temp);
		temp++;
		n--;
	}
	return (NULL);
}

// int main()
// {
// 	char s[] = {0, 1, 2, 3, 4};
// 	int c = 0;
// 	size_t n = 1;
// 	printf("%p", ft_memchr(s, c, n));
// 	printf("vrai memchr : %p\n", memchr(s, c, n));
// 	return 0;
// }
