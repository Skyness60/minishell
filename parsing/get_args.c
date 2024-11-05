/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:48:10 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/05 09:38:31 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	only_redirs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '<' && str[i] != '>')
			return (0);
	}
	return (1);
}

static char	*till_redir(t_data *data, char *str, t_execs *exec, int nb_words)
{
	int		i;
	char	*dest;

	i = -1;
	if (ignore_redir(data, exec, nb_words) == 1)
	{
		dest = ft_strdup(str);
		if (!dest)
			perror_exit("Error w/ malloc\n", 2, data);
		add_ptr(data->trash, dest);
		return (dest);
	}
	while (str[++i] && str[i] != '<' && str[i] != '>')
		;
	dest = ft_strndup(str, i);
	if (!dest)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, dest);
	return (dest);
}

static void	cp_args(t_data *data, t_execs *exec, char **tab)
{
	int	i;
	int	size;

	i = -1;
	size = 1;
	while (tab[++i])
		if (tab[i][0] != '<' && tab[i][0] != '>' && (i == 0 \
		|| only_redirs(tab[i - 1]) == 0))
			size++;
	if (size == 1)
		return ;
	exec->args = malloc(sizeof(char *) * (size + 1));
	if (!exec->args)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, exec->args);
	exec->args[0] = exec->cmd;
	i = 0;
	size = 1;
	while (tab[++i])
	{
		if ((tab[i][0] != '<' && tab[i][0] != '>') && (i == 0 \
		|| only_redirs(tab[i - 1]) == 0 || tab[i - 1][0] == '\0'))
			exec->args[size++] = till_redir(data, tab[i], exec, i);
	}
	exec->args[size] = NULL;
}

void	get_args(t_data *data, t_execs *exec)
{
	int		i;
	char	**tab;

	i = -1;
	tab = exec->tokens;
	while (tab[++i])
	{
		if (tab[i][0] != '<' && tab[i][0] != '>')
		{
			if (i != 0 && ((tab[i - 1][0] == '<' || tab[i - 1][0] == '>') &&
				only_redirs(tab[i - 1]) == 1))
				continue ;
			exec->cmd = till_redir(data, tab[i], exec, i);
			cp_args(data, exec, tab + i);
			break ;
		}
	}
}
