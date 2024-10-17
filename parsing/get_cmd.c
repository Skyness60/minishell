/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:03:47 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/17 13:50:39 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	inspect_cmd(char *str, t_data *data)
// {
// 	if (access(str, F_OK) == 0)
// 	{
// 		data->error = true;
		
// 	}
// }

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
		{
			exec->cmd = ft_strdup(tab[i]);
			break ;
		}
	}	
}	

void	get_cmd(t_data *data, t_execs *exec)
{
	char	**tab;

	tab = exec->tokens;
	if (array_len(tab) == 0)
		return ;
	else if (array_len(tab) == 1 && tab[0][0] != '<' && tab[0][0] != '>')
		exec->cmd = ft_strdup(tab[0]);
	else if (tab[0][0] != '<' && tab[0][0] != '>')
		exec->cmd = ft_strdup(tab[0]);
	else
		check_file_first(exec, tab);
	if (exec->cmd)
	{
		// inspect_cmd(exec->cmd, data);
		add_ptr(data->trash, exec->cmd);
	}
}
