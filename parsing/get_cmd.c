/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:33:17 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/02 16:08:20 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*find_file(t_data *data, char **tab, t_execs *exec)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = -1;
	dest = NULL;
	if (exec->infile || exec->outfile || exec->input)
	{
		while (tab[++i])
		{
			while (tab[i][++j])
			if (ft_strcmp(exec->infile, tab[i] + j) == 0 || \
			ft_strcmp(exec->outfile, tab[i] + j) == 0 \
			|| ft_strcmp(exec->input, tab[i] + j) == 0)
				dest = ft_strdup(tab[i + 1]);
		}
	}
	if (dest)
		add_ptr(data->trash, dest);
	return (dest);
}

void	get_cmd(t_data *data, t_execs *exec)
{
	char	**tab;
	char	*dest;
	
	tab = exec->to_exec;
	dest = find_file(data, tab, exec);
	if (dest == NULL)
	{
		exec->cmd = ft_strdup(tab[0]);
		add_ptr(data->trash, exec->cmd);
	}
	else
		exec->cmd = dest;
}
