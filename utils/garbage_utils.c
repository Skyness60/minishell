/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:25:50 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/09 13:39:37 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*dest;

	if (ptr == NULL)
		return (malloc(new_size));
	dest = malloc(new_size);
	if (!dest)
		perror_exit("Error w/ malloc\n", 1);
	ft_memcpy(dest, (const void *)ptr, old_size);
	free(ptr);
	return (dest);
}

void	init_garbage_collector(t_garb_c *trash)
{
	trash->capacite = 2;
	trash->count = 0;
	trash->ptr_arr = malloc(trash->capacite * sizeof(void *));
}

void	add_ptr(t_garb_c *trash, void *ptr)
{
	if (trash->count == trash->capacite)
	{
		trash->capacite *= 2;
		trash->ptr_arr = ft_realloc(trash->ptr_arr, trash->count * sizeof(void *), \
			sizeof(void *) * trash->capacite);
	}
	trash->ptr_arr[trash->count++] = ptr;
}

void	add_ptr_tab(t_garb_c *trash, void **ptr_arr, int arr_len, bool is_malloced)
{
	int	i;

	i = 0;
	while (i < arr_len)
		add_ptr(trash, ptr_arr[i++]);
	if (is_malloced == true)
		add_ptr(trash, ptr_arr);
}

void	free_all(t_garb_c *trash)
{
	size_t	i;

	i = 0;
	if (trash == NULL)
		return ;
	while (i < trash->count)
		free(trash->ptr_arr[i++]);
	trash->ptr_arr = NULL;
}
