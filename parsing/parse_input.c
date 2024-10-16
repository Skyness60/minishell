/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:29:55 by sperron           #+#    #+#             */
/*   Updated: 2024/10/16 18:04:52 by sperron          ###   ########.fr       */
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

int	ft_varlen(t_execs *exec, int start)
{
	int		i;
	int		len;
	bool	in_var;

	i = start - 2;
	len = 0;
	in_var = false;
	while (exec->cmd[++i])
	{
		if (exec->cmd[i] == '$' && in_var == false)
		{
			in_var = true;
			len++;
		}
		else if (in_var == true)
		{
			if (ft_isalnum(exec->cmd[i]) || exec->cmd[i] == '_')
				len++;
			else
				break ;
		}
	}
	return (len);
}

static void	ft_variables(t_data *data, t_execs *exec)
{
	int		i;
	int		j;
	int		len_var;
	bool	in_var;
	char	*result;
	char	*after_var;
	int		len;
	bool	malloced;

	in_var = false;
	i = -1;
	j = 0;
	after_var = NULL;
	len = 0;
	malloced = false;
	while (exec->cmd[++i])
	{
		if (exec->cmd[i] == '$' && in_var == false && malloced == false)
			in_var = true;
		if (in_var == true)
		{
			if (malloced == false)
			{
				len_var = ft_varlen(exec, i);
				result = malloc(sizeof(char *) * len_var);
				malloced = true;
				exec->cmd[i] = ' ';
				i++;
			}
			if (ft_isalnum(exec->cmd[i]) || exec->cmd[i] == '_')
			{
				result[j] = exec->cmd[i];
				exec->cmd[i] = ' ';
				j++;
			}
			else 
				in_var = false;
		}
		if (in_var == false && malloced == true)
		{
			j = i;
			while (exec->cmd[j])
				j++;
			after_var = malloc(sizeof(char *) * j + 1);
			j = -1;
			while (exec->cmd[i])
			{
				after_var[++j] = exec->cmd[i];	
				i++;
			}
		}
	}
	result = get_var_in_env(data->env, result, data);
	i = -1;
	j = -1;
	while (exec->cmd[++i])
	{
		if (exec->cmd[i] == ' ')
			while (result[++j])
				exec->cmd[i++] = result[j];
	}
	if (after_var)
		exec->cmd = ft_strjoin(exec->cmd, after_var);
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
	t_execs	*node;

	i = -1;
	data->pipes_to_ex = ft_calloc(size, sizeof(t_execs *));
	if (!data->pipes_to_ex)
		perror_exit("Error w/ malloc\n", 2);
	add_ptr(data->trash, (void *)data->pipes_to_ex);
	while (++i < (int)size)
	{
		create_node(data, pipes[i]);
		node = find_x_node(*data->pipes_to_ex, i);
		node->index = ++data->nb_execs;
		handle_heredoc(data, node);
		redirect(data, node);
		get_cmd(data, node);
		if (!(node->cmd))
			continue ;
		get_args(data, node);
		ft_variables(data, node);
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
	pipes = split_pipe(data->input, "|");
	if (!pipes)
		perror_exit("Error w/ malloc.\n", 1);
	if (create_execs(pipes, data, array_len(pipes)) != -1 && data->error == 0)
		pipeslines(data, data->pipes_to_ex, -1);
	return ;
}
