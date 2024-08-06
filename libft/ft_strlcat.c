/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:13:49 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/23 12:54:38 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char	*src, size_t n)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(dest);
	if (n <= i)
		return (n + ft_strlen(src));
	while (i + 1 < n && src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[j]));
}

// int main()
// {
// 	char *src = "hudzo";
// 	char dest[] = "ndiozcs";
// 	size_t	n = 0;
// 	printf("%s\n", ft_strlcat(dest, src, n));
//	printf("vrai strlcat : %s\n", strlcat(dest, src, n));
// 	return 0;
// }
