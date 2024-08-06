/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:12:30 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/20 12:12:31 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void	*dest, const void	*src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

// int	main()
// {
// 	char	*src[10];
// 	char	*dest[9];
// 	size_t	n = 6;
// 	printf("%p\n", ft_memmove(dest, src, n));
//	printf("vrai memmove : %p\n", ft_memmove(dest, src, n));
//	return 0;
// }
