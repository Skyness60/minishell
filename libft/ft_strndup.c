/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:05:46 by sperron           #+#    #+#             */
/*   Updated: 2024/09/23 12:06:18 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int n)
{
	char	*dup;

	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	ft_strncpy(dup, str, n);
	dup[n] = '\0';
	return (dup);
}
