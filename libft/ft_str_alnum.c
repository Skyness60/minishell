/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_alnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:27:03 by sperron           #+#    #+#             */
/*   Updated: 2024/09/16 11:29:28 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_alnum(const char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (!ft_isalnum((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}
