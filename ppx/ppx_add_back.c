/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:00:00 by sperron           #+#    #+#             */
/*   Updated: 2024/09/26 11:05:07 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppx.h"

int	ppx_add_back(t_ppx **ppx, t_ppx *ppx_new)
{
	t_ppx	*temp;

	if (!ppx_new)
		return (0);
	temp = *ppx;
	if (!temp)
	{
		*ppx = ppx_new;
		return (1);
	}
	while (temp->next)
		temp = temp->next;
	temp->next = ppx_new;
	ppx_new->prev = temp;
	return (1);
}
