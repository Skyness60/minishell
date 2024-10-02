/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/10/02 13:55:53 by jlebard          ###   ########.fr       */
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
	if (!node)
		perror_exit("Error w/ malloc\n", 2);
	add_ptr(data->trash, (void *)node);
	if (!*data->pipes_to_ex)
	{
		data->pipes_to_ex[0] = node;
		node->next = NULL;
		node->previous = NULL;
	}
	else
	{
		node->previous = find_last(*(data->pipes_to_ex));
		node->next = NULL;
		node->previous->next = node;
	}
	node->to_exec = split_if_quote(cmd_to_ex, " \t\n\v\f");
	add_ptr_tab(data->trash, (void **)node->to_exec, \
		(int)array_len(node->to_exec), false);
	node->tronque = false;
	node->infile = NULL;
	node->outfile = NULL;
	node->input = NULL;
}

static int	create_execs(char **pipes, t_data *data, size_t size)
{
	int	i;

	i = -1;	
	data->pipes_to_ex = malloc(size * sizeof(t_execs *));
	if (!data->pipes_to_ex)
		perror_exit("Error w/ malloc\n", 2);
	data->pipes_to_ex[0] = NULL;
	add_ptr(data->trash, (void *)data->pipes_to_ex);
	while (++i < (int)size)
	{
		create_node(data, pipes[i]);
		handle_heredoc(data, data->pipes_to_ex[i]);
		redirect(data, data->pipes_to_ex[i]);
	}
	free_tab(pipes);
	return (i + 1);
}

static void	display(t_data *data, size_t size)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (i < (int)size)
	{
		while (data->pipes_to_ex[i]->to_exec[++j])
			printf("%s\n", data->pipes_to_ex[i]->to_exec[j]);
		if (data->pipes_to_ex[i]->infile)
			printf("infile : %s\n", data->pipes_to_ex[i]->infile);		
		if (data->pipes_to_ex[i]->input)
			printf("input : %s\n", data->pipes_to_ex[i]->input);		
		if (data->pipes_to_ex[i]->outfile)
			printf("outfile : %s\n", data->pipes_to_ex[i]->outfile);
		i++;
	}
}

void	parse_input(t_data *data)
{
	char	**pipes;
	int		i;
	size_t	size;
	
	i = -1;
	pipes = NULL;
	if (just_space(data->input) == 1)
		return ;
	pipes = split_with_quotes(data->input, "|");
	size = array_len(pipes);
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1);
	if (create_execs(pipes, data, array_len(pipes)) > 1 && data->error == false)
		// execute_pipes(data, pipes);
		data->in_fd = 1;
	else if (data->error == false)
		// execute_cmd(data, (split_with_quotes(redirect(data->input, data), \
		// " \t\n\v\f")), data->in_fd, data->out_fd);
		data->in_fd = 1;
	display(data, size);
	return ;
}
