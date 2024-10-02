/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:12:40 by sperron           #+#    #+#             */
/*   Updated: 2024/09/30 11:11:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "../../libft.h"

int	ft_printf(const char *format, ...);
int	ft_dprintf(int fd, const char *format, ...);
int	ft_putpointer(void *adress, int fd);
int	ft_putstr(char *s, int fd);
int	ft_puthexa(char form, long double nbr, int fd);
int	ft_putchar(char c, int fd);
#endif