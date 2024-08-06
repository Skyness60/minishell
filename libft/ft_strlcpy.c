/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:13:57 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/23 13:07:38 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = (ft_strlen(src));
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}

// int main()
// {
// 	char		*dst;
// 	char	const	*src = "huwdiwh";
// 	size_t size = 3;
// 	printf("%ld + dst = %s\n", ft_strlcpy(dst, src, size), dst);
//	printf("vrai strlcpy : %ld + dst = %s\n", strlcpy(dst, src, size), dst);
// 	return 0;	
// }
