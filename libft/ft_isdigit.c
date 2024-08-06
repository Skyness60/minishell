/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:11:37 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/20 12:11:38 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

// int main()
// {
// 	char c = 'j';
// 	printf("%d\n", ft_isdigit(c));
//	printf("vrai isdigit : %d\n", isdigit(c));
//	return 0;
// }
