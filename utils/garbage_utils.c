/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:25:50 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/12 10:00:57 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_garbage_collector(t_garb_c *trash)
{
	trash->ptr_arr = NULL;
	trash->count = 0;
}

void	add_ptr(t_garb_c *trash, void *ptr)
{
	void	**temp;
	int		i;
	
	i = -1;
	trash->count++;
	temp = malloc(trash->count * sizeof(void *));
	if (!temp)
		perror_exit("Error w/ malloc.\n", 1);
	if (trash->ptr_arr)
	{
		while (trash->ptr_arr[++i])
			temp[i] = trash->ptr_arr[i];
		temp[i] = ptr;
		free(trash->ptr_arr);
	}
	else
		temp[0] = ptr;
	trash->ptr_arr = temp;
}

void	add_ptr_tab(t_garb_c *trash, void **ptr_arr)
{
	int	i;

	i = -1;
	while (ptr_arr[++i] != NULL)
		add_ptr(trash, ptr_arr[i]);
}


void	free_all(t_garb_c *trash)
{
	int	i;

	i = 0;
	if (trash == NULL)
		return ;
	while (trash->ptr_arr[i] != NULL)
	{
		free(trash->ptr_arr[i]);
		i++;
	}
}
