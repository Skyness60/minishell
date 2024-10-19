/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/10/17 16:39:30 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#define PATH_SIZE 1024

int	just_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t' || str[i] != '\n' || \
		str[i] != '\v' || str[i] != '\f' || str[i] != '\r')
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
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, (void *)node);
	if (!*data->pipes_to_ex)
	{
		*data->pipes_to_ex = node;
		node->previous = NULL;
	}
	else
	{
		node->previous = find_last(*(data->pipes_to_ex));
		node->previous->next = node;
	}
	node->infile = NULL;
	node->outfile = NULL;
	node->input = NULL;
	node->next = NULL;
	node->cmd = NULL;
	node->tokens = split_with_quotes(cmd_to_ex, " \t\n\v\f");
	replace_vars_in_tokens(node->tokens, data);
	node->tronque = false;
	add_ptr_tab(data->trash, (void **)node->tokens, \
		(int)array_len(node->tokens), true);
}

static int	create_execs(char **pipes, t_data *data, size_t size)
{
	int	i;
	t_execs	*node;

	i = -1;
	data->pipes_to_ex = ft_calloc(size, sizeof(t_execs *));
	if (!data->pipes_to_ex)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, (void *)data->pipes_to_ex);
	while (++i < (int)size)
	{
		create_node(data, pipes[i]);
		node = find_x_node(*data->pipes_to_ex, i);
		node->g_data = data;
		node->index = ++data->nb_execs;
		redirect(data, node);
		get_cmd(data, node);
		if (!(node->cmd))
			continue ;
		get_args(data, node);
		//ft_variables(data, node);
	}
	if (!data->error)
		check_infiles(data);
	return (free_tab(pipes), i);
}

void	parse_input(t_data *data)
{
	char	**pipes;
		
	pipes = NULL;
	if (just_space(data->input) == 1 || ft_strcmp(data->input, "!") == 0 || \
	ft_strcmp(data->input, ":") == 0)
		return ;
	if (syntax_error(data->input) == 1)
		return ;
	pipes = split_pipe(data->input, "|");
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1, data);
	if (create_execs(pipes, data, array_len(pipes)) != -1 \
	&& data->error == false)
		pipeslines(data, data->pipes_to_ex, -1);
	return ;
}
