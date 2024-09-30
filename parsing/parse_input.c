/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/09/30 09:46:57 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	just_space(char *str)
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
	int		i;
	
	i = -1;
	pipes = NULL;
	nb_parts = 0;
	// handle_heredoc(data);
	if (just_space(data->input) == 1)
		return ;
	pipes = split_with_quotes(data->input, "|");
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1);
	nb_parts = array_len(pipes);
	if (array_len(pipes) > 1)
	{
		while (++i < (int)array_len(pipes))
			pipes[i] = redirect(pipes[i], data);
		execute_pipes(data, pipes, nb_parts);
	}
	else
		execute_cmd(data, (split_with_quotes(redirect(data->input, data), \
		" \t\n\v\f")), data->in_fd, data->out_fd);
}
