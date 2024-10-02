/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/10/02 15:08:22 by sperron          ###   ########.fr       */
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
	node->tronque = false;
	node->infile = NULL;
	node->outfile = NULL;
}

static int	create_execs(char **pipes, t_data *data, size_t size)
{
	int	i;

	i = -1;	
	data->pipes_to_ex = malloc(size * sizeof(t_execs *));
	if (!data->pipes_to_ex)
		perror_exit("Error w/ malloc\n", 2);
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

static void	display(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (data->pipes_to_ex[++i])
	{
		while (data->pipes_to_ex[i]->to_exec[++j])
			printf("%s\n", data->pipes_to_ex[i]->to_exec[j]);
		if (data->pipes_to_ex[i]->infile)
			printf("%s\n", data->pipes_to_ex[i]->infile);		
		if (data->pipes_to_ex[i]->input)
			printf("%s\n", data->pipes_to_ex[i]->input);		
		if (data->pipes_to_ex[i]->outfile)
			printf("%s\n", data->pipes_to_ex[i]->outfile);
	}
}

void	parse_input(t_data *data)
{
	char	**pipes;
	int		i;
	char	**cmds;
	
	i = -1;
	pipes = NULL;
	if (just_space(data->input) == 1)
		return ;
	pipes = split_with_quotes(data->input, "|");
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1);
	if (create_execs(pipes, data, array_len(pipes)) > 1 && data->error == false)
		// execute_pipes(data, pipes);
		data->in_fd = 0;
	if (data->error == false)
	{
		redirect(data, *(data->pipes_to_ex));
		cmds = split_with_quotes(data->pipes_to_ex[0]->to_exec[0], " \t\f\v\n");
		execute_cmd(data, cmds, data->in_fd, data->out_fd);
	}

	display(data);
	return ;
}
