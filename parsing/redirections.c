/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:12:08 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/01 12:13:33 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	last_chara(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (false);
	return (true);
}

static void	err_rd(char *str, t_data *data)
{
	write(2, str, ft_strlen(str));
	data->error = true;
}

static char	*redirect_infile(t_data *data, t_execs *exec, int i)
{
	char	**tab;

	tab = exec->to_exec;	
	if (last_chara(tab[i], '<') && (!tab[i + 1] || !tab[i + 1][0]))
		err_rd("bash: syntax error near unexpected token `newline'", data);
	if (tab[i][1] == '<' && tab[i][2] == '<' && tab[i][3])
	{
		if (tab[i][3] == '<' && tab[i][4] != '<')
			err_rd("bash: syntax error near unexpected token `<'", data);
		else if (tab[i][3] == '<' && tab[i][5] != '<')
			err_rd("bash: syntax error near unexpected token `<<'", data);
		else if (tab[i][3] == '<' && tab[i][5] == '<')
			err_rd("bash: syntax error near unexpected token `<<<'", data);
		else if (tab[i][3] != '<')
			exec->input = ft_strdup(tab[i] + 3);
		else
			exec->input = ft_strdup(tab[i + 1]);
	}
	else if (tab[i][1])
		exec->infile = ft_strdup(tab[i] + 1);
	else
		exec->infile = ft_strdup(tab[i + 1]);
}


static char	*redirect_outfile(t_data *data, t_execs *exec, int i)
{
	char	**tab;
	
	tab = exec->to_exec;
	if (last_chara(tab[i], '>') && (!tab[i + 1] || !tab[i + 1][0]))
		err_rd("bash: syntax error near unexpected token `newline'", data);
	if (tab[i][1] == '>')
	{
		if (tab[i][3] == '>')
			err_rd("bash: syntax error near unexpected token `>>'", data);
		else
			err_rd("bash: syntax error near unexpected token `>'", data);
		if (tab[i][2])
			exec->outfile = ft_strdup(tab[i] + 2);
		else
			exec->outfile = ft_strdup(tab[i + 1]);
	}
	else
	{
		exec->tronque = true;
		if (tab[i][1])
			exec->outfile = ft_strdup(tab[i] + 1);
		else
			exec->outfile = ft_strdup(tab[i + 1]);	
	}
}

void	redirect(t_data *data, t_execs *exec)
{
	int	i;
	
	i = -1;
	while (exec->to_exec[++i])
	{
		if (exec->to_exec[i][0] == '<')
			redirect_infile(data, exec, i);
		else if (exec->to_exec[++i] == '>')
			redirect_outfile(data, exec, i);
		if (exec->infile)
			add_ptr(data->trash, exec->infile);
		if (exec->outfile)
			add_ptr(data->trash, exec->outfile);
		if (exec->input)
			add_ptr(data->trash, exec->input);
	}
}
