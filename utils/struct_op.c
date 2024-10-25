/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:10:37 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/25 12:52:42 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	size_struct(t_execs *first)
{
	size_t	i;
	t_execs	*temp;

	temp = first;
	i = 1;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

t_execs	*find_last(t_execs *first)
{
	t_execs	*node;

	node = first;
	while (node->next != NULL)
		node = node->next;
	return (node);
}

t_execs	*find_x_node(t_execs *first, int x)
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
