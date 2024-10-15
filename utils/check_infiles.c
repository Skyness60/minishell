/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:23:24 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/15 11:11:48 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_struct(t_data *data)
{
	data->save_infiles = malloc(sizeof(t_save_infiles));
	add_ptr(data->trash, data->save_infiles);
	data->save_infiles->capacity = 1;
	data->save_infiles->count = 0;
	data->save_infiles->names = malloc(sizeof(char *));
}

void	add_infile(t_data *data, char *name)
{
	if (!data->save_infiles)
	{
		init_struct(data);
		if (!data->save_infiles || !data->save_infiles->names)
			perror_exit("Error w/ malloc", 2);
	}
	if (data->save_infiles->count == data->save_infiles->capacity)
	{
		data->save_infiles->capacity *= 2;
		data->save_infiles->names = ft_realloc((void *)data->save_infiles->names,\
		data->save_infiles->count * sizeof(char *),\
		data->save_infiles->capacity * sizeof(char *));
	}
	data->save_infiles->names[data->save_infiles->count] = ft_strdup(name);
	if (!data->save_infiles->names[data->save_infiles->count])
		perror_exit("Error w/ malloc", 2);
	add_ptr(data->trash, data->save_infiles->names[data->save_infiles->count]);
	data->save_infiles->count++;
}

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

bool	last_chara(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (false);
	return (true);
}
