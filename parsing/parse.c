/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:51:58 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/10 12:19:47 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_tab(char **dbl_arr)
{
	int	i;
	
	i = 0;
	while (dbl_arr[i])
		i++;
	return  (i);
}

void	ft_parse(t_data *data)
{
	int		nb_parts;
	char **pipes;
	
	if (just_space(data->input) == 1)
		return (-1);
	pipes = split_if_quote(data->input, '|');
	if (!pipes)
		return (-1);
	nb_parts = len_tab(pipes);
	if (count_pipes(data->input) > )		
}
