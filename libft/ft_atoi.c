/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:10:54 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/20 12:10:58 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char	*str)
{
	char	*temp;
	int		i;
	int		n;
	int		j;

	temp = (char *)str;
	i = 0;
	n = 0;
	j = 0;
	while ((temp[i] > 8 && temp[i] < 14) || (temp[i] == 32))
		i++;
	if (temp[i] == 43 || temp[i] == 45)
	{
		if (temp[i] == 45)
			n++;
		i++;
	}
	while (temp[i] > 47 && temp[i] < 58)
	{
		j = j * 10 + (temp[i] - 48);
		i++;
	}
	if (n == 1)
		return (-j);
	return (j);
}

// int main()
// {
// 	char *str = "   \t\n\f -67263ghsgsw76382";
// 	printf("%d\n", ft_atoi(str));
// 	printf("vrai atoi : %d\n",atoi(str));
//	return 0;
// }
