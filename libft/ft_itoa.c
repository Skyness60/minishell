/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:12:02 by jlebard           #+#    #+#             */
/*   Updated: 2023/11/29 13:06:47 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_size(int n)
{
	int	temp;
	int	i;

	temp = n;
	i = 1;
	if (n == -2147483648)
	{
		i = 11;
		return (i);
	}
	while (temp <= -10 || temp >= 10)
	{
		temp = temp / 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}

static char	*write_itoa(int n, int len, int i)
{
	char	*dest;

	dest = malloc((len + 1) * sizeof(char));
	if (n == -2147483648)
	{
		dest[0] = '-';
		dest[1] = '2';
		n = 147483648;
		i = 2;
	}
	if (n < 0)
	{
		dest[0] = '-';
		n = -n;
		i++;
	}
	dest[len] = '\0';
	while (i < len)
	{
		len--;
		dest[len] = (n % 10) + 48;
		n = n / 10;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;

	len = ft_itoa_size(n);
	dest = write_itoa(n, len, 0);
	if (!dest)
		return (NULL);
	return (dest);
}

// int main ()
// {
// 	int n = -3273826;
// 	printf("%s\n", ft_itoa(n));
// 	return 0;
// }
