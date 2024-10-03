/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:33:17 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/03 09:15:32 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_file_first(t_execs *exec, char **tab)
{
	size_t	size;
	int		i;

	i = -1;
	size = array_len(tab);
	if (size <= 2)
		return ;
	while (++i < (int)size)
	{
		if (tab[i][0] == '<' || tab[i][0] == '>')
		{
			if (last_chara(tab[i], '<') == 0 || last_chara(tab[i], '>') == 0)
			{
				i++;
				continue ;			
			}
			else
				continue ;
		}
		else
			exec->cmd = ft_strdup(tab[i]);
	}	
}	

void	get_cmd(t_data *data, t_execs *exec)
{
	char	**tab;
	int		i;

	i = -1;
	tab = exec->to_exec;
	if (array_len(tab) == 1)
		exec->cmd = ft_strdup(tab[0]);
	else if (tab[0][0] != '<' && tab[0][0] != '>')
		exec->cmd = ft_strdup(tab[0]);
	else
		check_file_first(exec, tab);
	if (exec->cmd)
		add_ptr(data->trash, exec->cmd);
}
