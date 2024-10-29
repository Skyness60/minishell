/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:23:24 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/29 07:59:30 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_infiles(t_data *data)
{
	char	**tab;
	char	*str;
	char	*msg;
	int		i;

	if (!data->save_infiles)
		return ;
	i = -1;
	tab = data->save_infiles->names;
	while (++i < (int)data->save_infiles->count && data->error == false)
	{
		if (access(tab[i], F_OK) == -1)
		{
			str = ft_strjoin("bash: ", tab[i]);
			msg = ft_strjoin_free_s1(str, ": No such file or directory\n");
			add_ptr(data->trash, msg);
			write (2, msg, ft_strlen(msg));
			data->error = true;
		}
	}
}

bool	last_chara(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	if (str[i] == '<' || str[i] == '>')
		return (true);
	return (false);
}
