/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:10:37 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/30 15:13:15 by jlebard          ###   ########.fr       */
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
