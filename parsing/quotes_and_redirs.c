/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_redirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:25:52 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/01 15:40:51 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ignore_redir(t_data *data, t_execs *exec, int nb)
{
	int	i;

	i = -1;
	if (!data->quote_id)
		return (false);
	while (++i < data->count_quoted)
	{
		if (exec->index == data->quote_id[i][0] && nb == data->quote_id[i][1])
			return (true);
	}
	return (false);
}

static bool	is_in_quotes_or_double(char *str, int pos)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] && i < pos)
		if (str[i] == '\'')
			count++;
	if (count % 2 == 1)
		return (true);
	else
		return (false);
}

static int	till_next_quote(t_data *data, int words, int pipes, int res)
{
	int	i;
	
	i = res;
	while (data->input[++i] && data->input[i] != data->input[res])
		;
	data->quote_id[data->count_quoted][0] = pipes;
	data->quote_id[data->count_quoted++][1] = words;
	return (i);
}

static int	set_place_of_quote(char *input, int	pos, t_data *data)
{
	int	i;
	int	words;
	int	pipes;
	int	res;
	
	i = -1;
	words = 0;
	pipes = 1;
	while (input[++i] && i < pos)
	{
		if (input[i] == '|' && !is_in_quotes_or_double(input, input[i]))
			pipes++;
	}
	res = i;
	while (--i >= 0 && input[i] != '|')
	{
		if (ft_isspace(input[i]) == 1 && \
			!is_in_quotes_or_double(input, input[i]))
		{
			words++;
			while (input[i] && ft_isspace(input[i]) == 1)
				i--;
		}
	}
	return (till_next_quote(data, words, pipes, res));
}

void	identify_quotes(char *input, t_data *data)
{
	int	i;
	int	count;
	
	i = -1;
	count = 0;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
			count++;
	}
	if (count == 0)
		return ;
	data->quote_id = malloc(count / 2 * sizeof(int[2]));
	if (!data->quote_id)
		perror_exit("Error w/ malloc\n" , 2, data);
	add_ptr(data->trash, data->quote_id);
	i = -1;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
			i = set_place_of_quote(input, i, data);
	}
}
