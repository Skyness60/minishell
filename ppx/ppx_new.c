/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:58:28 by sperron           #+#    #+#             */
/*   Updated: 2024/09/26 10:58:35 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ppx.h"

t_ppx	*ppx_new(char **envp)
{
	t_ppx	*new;

	new = (t_ppx *)malloc(sizeof(t_ppx));
	if (!new)
		return (NULL);
	new->envp = envp;
	new->next = NULL;
	new->prev = NULL;
	new->paths = find_paths(envp);
	if (!new->paths)
		return (free(new), ft_free_strs(new->paths), NULL);
	return (new);
}
