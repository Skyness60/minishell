/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:11:30 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/20 12:11:32 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

// int main()
// {
//     char c = 'h';
//     printf("%d\n", ft_isascii(c));
//	   printf("vrai isascii : %d\n", isascii(c));
//     return 0;
// }
