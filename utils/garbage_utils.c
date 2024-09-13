/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:25:50 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/13 10:00:53 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_garbage_collector(t_garb_c *trash)
{
	trash->ptr_arr = NULL;
	trash->count = 0;
}

void	add_ptr(t_garb_c *trash, void *ptr)
{
	void	**temp;
	size_t	i;

	i = 0;
	trash->count++;
	temp = malloc(trash->count * sizeof(void *));
	if (!temp)
		perror_exit("Error w/ malloc.\n", 1);
	if (trash->ptr_arr)
	{
		while (i < trash->count - 1)
		{
			temp[i] = trash->ptr_arr[i];
			i++;
		}
		temp[i] = ptr;
		free(trash->ptr_arr);
	}
	else
		temp[0] = ptr;
	trash->ptr_arr = temp;
}

void	add_ptr_tab(t_garb_c *trash, void **ptr_arr, int arr_len)
{
	size_t	i;

	i = 0;
	while (i < (size_t)arr_len)
	{
		add_ptr(trash, ptr_arr[i]);
		i++;
	}
}

void	free_all(t_garb_c *trash)
{
	int	i;

	i = 0;
	if (trash == NULL)
		return ;
	while (i < (int)trash->count)
	{
		free(trash->ptr_arr[i]);
		i++;
	}
}
