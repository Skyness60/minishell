/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:58:26 by sperron           #+#    #+#             */
/*   Updated: 2024/09/30 11:11:17 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_printadress(const unsigned long n, int fd)
{
	if (n / 16)
		return (ft_printadress(n / 16, fd) + ft_printadress(n % 16, fd));
	else if (!(n / 10))
		ft_putchar(n + '0', fd);
	else
		ft_putchar((char) n - 10 + 'a', fd);
	return (1);
}

int	ft_putpointer(void *adress, int fd)
{
	if (!adress)
		return (ft_putstr("(nil)", fd));
	ft_putstr("0x", fd);
	return (2 + ft_printadress((unsigned long) adress, fd));
}

int	ft_putstr(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_puthexa(char form, long double nbr, int fd)
{
	int		count;
	char	*hexa;

	count = 0;
	hexa = NULL;
	if (form == 'x')
		hexa = "0123456789abcdef";
	else if (form == 'X')
		hexa = "0123456789ABCDEF";
	if (nbr < 0)
	{
		nbr = -nbr;
		write(1, "-", 1);
		count++;
	}
	if (nbr >= 16)
		count += ft_puthexa(form, ((unsigned long) nbr / 16), fd);
	ft_putchar(hexa[(unsigned long)nbr % 16], fd);
	count++;
	return (count);
}

int	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
