/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:11:43 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/22 15:58:38 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

// int main ()
// {
//     char c = 6;
//     printf("%d\n", ft_isprint(c));
//	   printf("vrai isprint : %d\n", isprint(c));
//     return 0;
// }