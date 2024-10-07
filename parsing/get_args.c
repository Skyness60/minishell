/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:48:10 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/07 14:24:17 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cp_one_arg(t_data *data, t_execs *exec)
{
	exec->args = malloc(sizeof(char *) * 2);
	if (!exec->args)
		perror_exit("Error w/ malloc\n", 2);
	exec->args[0] = ft_strdup(exec->cmd);
	if (!exec->args[0])
		perror_exit("Error w/ malloc\n", 2);
	add_ptr(data->trash, exec->args[0]);
	exec->args[1] = NULL;
}

static int	till_last_file(char	**tab, int i)
{
	while (tab[i])
	{
		if (tab[i][0] == '<' || tab[i][0] == '>')
		{
			if (last_chara(tab[i], '<') || last_chara(tab[i], '>'))
			{
				if (tab[i + 1] && tab[i + 2])
					i+=1;
				else
					return (0);
			}
			else if (!tab[i + 1])
				return (0);
			i++;
		}
		else
			return (i);
	}
	return (0);
}

static void	cp_args(t_data *data, t_execs *exec, char **tab, int i)
{
	int	j;

	j = 0;
	while (tab[i + j] && tab[i + j][0] != '>' && tab[i + j][0] != '<')
		j++;
	exec->args = malloc(sizeof(char *) * (j + 2));
	j = 0;
	exec->args[j++] = ft_strdup(exec->cmd);
	if (!exec->args)
		perror_exit("Error w/ malloc\n", 2);
	add_ptr(data->trash, exec->args[0]);
	while (tab[i] && tab[i][0] != '<' && tab[i][0] != '>')
	{
		exec->args[j] = ft_strdup(tab[i++]);
		if (!exec->args[j])
			perror_exit("Error w/ malloc\n", 2);
		add_ptr(data->trash, exec->args[j]);
		j++;
	}
	exec->args[j] = NULL;	
}

void	get_args(t_data *data, t_execs *exec)
{
	int		i;
	char	**tab;

	i = -1;
	tab = exec->tokens;
	while (tab[++i])
	{
		if (ft_strcmp(exec->cmd, tab[i]) == 0)
		{
			if (!tab[i + 1])
				cp_one_arg(data, exec);
			else if (tab[i + 1][0] == '<' || tab[i + 1][0] == '>')
			{
				i = till_last_file(tab, i + 1);
				if (i == 0)
					cp_one_arg(data, exec);
				else
					cp_args(data, exec, tab, i + 1);
			}
			else
				cp_args(data, exec, tab, i + 1);
			break ;
		}
	}
}
