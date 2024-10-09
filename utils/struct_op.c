/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:10:37 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/10 00:51:47 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_execs	*find_last(t_execs *first)
{
	t_execs	*node;

	node = first;
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_execs *find_x_node(t_execs *first, int x)
{
	t_execs	*node;
	int		i;

	i = 0;	
	node = first;
	while (node->next != NULL && i < x)
	{
		node = node->next;
		i++;
	}
	return (node);
}
