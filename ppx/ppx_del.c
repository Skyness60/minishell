/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:00:20 by sperron           #+#    #+#             */
/*   Updated: 2024/09/26 11:00:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppx.h"

void	ppx_del(t_ppx **ppx)
{
	t_ppx	*temp;
	t_ppx	*save;

	temp = *ppx;
	if (!temp)
		return ;
	while (temp->prev)
		temp = temp->prev;
	while (temp)
	{
		save = temp->next;
		ft_free_strs(temp->paths);
		free(temp);
		temp = save;
	}
	*ppx = NULL;
}
