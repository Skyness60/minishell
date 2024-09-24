/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/09/24 14:02:48 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_tab(char **dbl_arr)
{
	int	i;

	i = 0;
	while (dbl_arr[i])
		i++;
	return (i);
}

int	count_pipes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

static int	just_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
			return (0);
		i++;
	}
	return (1);
}

void	parse_input(t_data *data)
{
	int		nb_parts;
	char	**pipes;	

	handle_heredoc(data);
	if (just_space(data->input) == 1)
		return ;
	pipes = split_if_quote(data->input, "|");
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1);
	nb_parts = len_tab(pipes);
	if (count_pipes(data->input) > 1)
		execute_pipes(data, pipes, nb_parts);
	else
		execute_cmd(data, split_with_quotes(data->input, " \t\n\v\f"), \
		data->in_fd, data->out_fd);
}
