/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:14:04 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/10 02:06:11 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str)
		i++;
	return (i);
}

// int main()
// {
// 	char *c = "   ";
// 	printf("%d", ft_strlen(c));
//	printf("vrai strlen : %d", strlen(c));
// 	return 0;
// }
