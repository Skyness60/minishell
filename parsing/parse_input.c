/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/09/30 15:21:11 by jlebard          ###   ########.fr       */
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

static void	create_node(t_data *data, char *cmd_to_ex)
{
	t_execs	*node;

	node = malloc(sizeof(t_execs));
	if (*data->pipes_to_ex == NULL)
	{
		data->pipes_to_ex[0] = node;
		node->next = NULL;
		node->previous = NULL;
	}
	else
	{
		node->previous = find_last(*data->pipes_to_ex);
		node->next = NULL;
		node->previous->next = node;
	}
	node->to_exec = split_if_quote(cmd_to_ex, " \t\n\v\f");
	add_ptr_tab(data->trash, (void **)node->to_exec, \
		(int)array_len(node->to_exec), false);
}

static void	create_execs(char **pipes, t_data *data, size_t size)
{
	int	i;

	i = -1;	
	data->pipes_to_ex = malloc(size * sizeof(t_execs *));
	if (!data->pipes_to_ex);
		perror_exit("Error w/ malloc\n", 2);
	add_ptr(data->trash, (void *)data->pipes_to_ex);
	while (++i < size)
		create_node(data, pipes[i]);
}

void	parse_input(t_data *data)
{
	char	**pipes;
	int		i;
	
	i = -1;
	pipes = NULL;
	// handle_heredoc(data);
	if (just_space(data->input) == 1)
		return ;
	pipes = split_with_quotes(data->input, "|");
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1);
	create_execs(pipes, data, array_len(pipes));
	if (array_len(pipes) > 1)
	{
		data->pipes_to_ex = redirect(pipes, data);
		free_tab(pipes);
		execute_pipes(data, pipes, nb_parts, ar);
	}
	else
		execute_cmd(data, (split_with_quotes(redirect(data->input, data), \
		" \t\n\v\f")), data->in_fd, data->out_fd);
}
