/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/21 01:19:15 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_error(char *argv, int status, int fd)
{
	if (status == 1)
		ft_dprintf(fd, "bash: export: '%s' :not a valid identifier\n", argv);
 	else if (status == 2)
		ft_dprintf(fd, "bash: export: -%c: invalid option\n", argv[1]);
	return (1);
 }


char	**ft_realloc_char(char **ptr, size_t old_size, size_t new_size)
{
	char	**dest;
	size_t	i;
	
	i = -1;
	if (ptr == NULL)
		return (malloc(new_size));
	dest = malloc(new_size);
	while (++i < (old_size / sizeof(char *)))
	{
		dest[i] = ft_strdup(ptr[i]);
		free(ptr[i]);
	}
	free(ptr);
	return (dest);
}