/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:14:41 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/18 14:56:47 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char	*s1, const char	*s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if (n <= 0)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != s2[i] && i != n)
		return (s1[i] - s2[i]);
	i++;
	return (0);
}

// void main()
// {
// 	char *s1 = "dhwohid";
// 	char *s2 = "dhwohPd";
// 	size_t n = 6;
// 	printf("%d", ft_strncmp(s1, s2, n));
// 	printf("%d", strncmp(s1, s2, 1));
// }
