/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:24:14 by sperron           #+#    #+#             */
/*   Updated: 2024/09/30 11:08:56 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppx.h"

void	close_pipe(t_ppx *ppx)
{
	if (!ppx)
		return ;
	while (ppx->prev)
		ppx = ppx->prev;
	while (ppx)
	{
		close(ppx->pipe_fd[0]);
		close(ppx->pipe_fd[1]);
		ppx = ppx->next;
	}
}
