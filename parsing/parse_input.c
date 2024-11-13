/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/11/13 11:10:14 by sperron          ###   ########.fr       */
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
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && \
		str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
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
	node->tronque = false;
	add_ptr_tab(data->trash, (void **)node->tokens, \
	(int)array_len(node->tokens), true);
}

static int	create_execs(char **pipes, t_data *data, size_t size)
{
	int		i;
	t_execs	*node;

	i = -1;
	data->pipes_to_ex = ft_calloc(size, sizeof(t_execs *));
	if (!data->pipes_to_ex)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, (void *)data->pipes_to_ex);
	while (data->error == false && ++i < (int)size)
	{
		create_node(data, pipes[i]);
		node = find_x_node(*data->pipes_to_ex, i);
		node->g_data = data;
		node->index = ++data->nb_execs;
		redirect(data, node);
		get_args(data, node);
	}
	if (!data->error)
		check_infiles(data);
	return (free_tab(pipes), i);
}

static char	*continue_quotes(char *str, t_data *data)
{
	int		counter;
	int		i;
	char	*res;
	int		status_quotes;

	counter = 0;
	status_quotes = 0;
	i = -1;
	res = NULL;
	while (str[++i])
	{
		if (is_quote(str[i], &status_quotes))
			counter++;
	}
	if (status_quotes != 2 && status_quotes != 0 && i > 0)
		res = prompt_command_singlequote(str);
	else if (status_quotes != 1 && status_quotes != 0 && i > 0)
		res = prompt_command_doublequote(str);
	else
		res = ft_strdup(str);
	add_ptr(data->trash, (void *)res);
	return (res);
}

void	parse_input(t_data *data)
{
	char	**pipes;

	pipes = NULL;
	data->input = continue_quotes(data->input, data);
	data->input = split_redirs(data, data->input);
	if (just_space(data->input) == 1)
		return ;
	if (ft_strcmp(data->input, "!") == 0 || ft_strcmp(data->input, ":") == 0 \
	|| syntax_error(data->input) == 1)
	{
		data->cmd_exit_status = 2;
		return ;
	}
	pipes = split_pipe(data->input, "|");
	identify_quotes(data->input, data);
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1, data);
	if (create_execs(pipes, data, array_len(pipes)) != -1 \
	&& data->error == false)
		pipeslines(data, data->pipes_to_ex, -1);
	else
		data->cmd_exit_status = 127;
	return ;
}
