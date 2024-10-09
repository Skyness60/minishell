/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/10/09 16:40:57 by sperron          ###   ########.fr       */
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
		if (!(str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_variables(t_data *data, t_execs *exec)
{
	int		i;
	int		j;
	char	**tab;
	char	*temp;
	
	temp = NULL;
	tab = exec->args;
	i = -1;
	j = -1;
	while (tab[++i])
	{
		// if (ft_strcmp(tab[i], "$?") == 0)
		// {
		// 	free(tab[i]);
		// 	tab[i] = ft_itoa((int)exit_status);
		// 	if (!tab[i])
		// 		perror_exit("Error w/ malloc\n", 2);
		// 	add_ptr(data, tab[i]);
		// }
		if (tab[i][0] == '$')
			temp = get_var_in_env(data->env, tab[i] + 1, data);
		if (temp)
			tab[i] = temp;			
	}
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
	int	i;

	i = -1;	
	data->pipes_to_ex = ft_calloc(size, sizeof(t_execs *));
	if (!data->pipes_to_ex)
		perror_exit("Error w/ malloc\n", 2);
	add_ptr(data->trash, (void *)data->pipes_to_ex);
	while (++i < (int)size)
	{
		create_node(data, pipes[i]);
		handle_heredoc(data, find_x_node(*data->pipes_to_ex, i));
		redirect(data, find_x_node(*data->pipes_to_ex, i));
		get_cmd(data, find_x_node(*data->pipes_to_ex, i));
		get_args(data, find_x_node(*data->pipes_to_ex, i));
		ft_variables(data, find_x_node(*data->pipes_to_ex, i));
	}
	if (!data->error)
		check_infiles(data);
	free_tab(pipes);
	return (i + 1);
}

void	parse_input(t_data *data)
{
	char	**pipes;
	size_t	size;
		
	pipes = NULL;
	if (just_space(data->input) == 1)
		return ;
	pipes = split_with_quotes(data->input, "| \t\n\v\f");
	size = array_len(pipes);
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1);
	if (create_execs(pipes, data, array_len(pipes)) > 1 && data->error == false)
		// execute_pipes(data, pipes);
		data->in_fd = 0;
	if (data->error == false)
	{
		redirect(data, *(data->pipes_to_ex));
		execute_cmd(data, data->pipes_to_ex);
	}
	return ;
}
