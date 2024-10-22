/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:12:08 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/22 12:18:30 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redirect_infile(t_data *data, t_execs *exec, int i)
{
	char	**tab;

	tab = exec->tokens;
	if (ft_strlen(tab[i]) == 1 && !tab[i + 1])
		err_rd("bash: syntax error near unexpected token `newline'\n", data);
	else if (last_chara(tab[i], '<') == 1 && \
		checker_redirect_in(tab[i + 1], data, false) == 1)
		return ;
	else if (checker_redirect_in(tab[i] + 1, data, true) == 1)
		return ;
	else if (last_chara(tab[i], '<') == 1)
		exec->infile = ft_strdup(tab[i + 1]);
	else
		exec->infile = ft_strdup(tab[i] + 1);
	if (exec->infile)
		add_ptr(data->trash, (void *)exec->infile);
}

static void	redirect_outfile(t_data *data, t_execs *exec, int i)
{
	char	**tab;
	int		count;
	
	tab = exec->tokens;
	count = 0;
	while (tab[i][count] == '>')
		count++;
	if (last_chara(tab[i], '>') && !tab[i + 1])
		return err_rd("bash: syntax error near unexpected token `newline'\n" \
			, data);
	else if (last_chara(tab[i], '<') == 1 && \
		checker_redirect_out(tab[i + 1], data, false) == 1)
		return ;
	else if (checker_redirect_out(tab[i] + count, data, true) == 1)
		return ;
	if (count == 1)
		exec->tronque = true;
	if (last_chara(tab[i], '>') == 1)
		exec->outfile = ft_strdup(tab[i + 1]);
	else
		exec->outfile = ft_strdup(tab[i] + count);
	if (exec->outfile)
		add_ptr(data->trash, (void *)exec->outfile);
}

int	redirect(t_data *data, t_execs *exec)
{
	int	i;
	
	i = -1;
	while (exec->tokens[++i] && data->error == false)
	{
		if (is_heredoc(exec->tokens[i]) == 1 || \
			is_input_heredoc(exec->tokens[i]))
		{
			if (handle_heredoc(data, exec) == 1)
				return (1);
		}	
		else if (exec->tokens[i][0] == '<')
		{
			redirect_infile(data, exec, i);
			if (exec->infile)
				add_infile(data, exec->infile);
		}
		else if (exec->tokens[i][0] == '>')
			redirect_outfile(data, exec, i);
	}
	return (0);
}
