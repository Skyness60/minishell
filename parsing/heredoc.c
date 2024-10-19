/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:06:27 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/17 16:41:19 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_delim_bis(char *str)
{
	char	*eof;
	size_t	len;
	int		i;
	
	len = 0;
	i = -1;	
	while (str[++i] && (str[i] < 8 || str[i] > 14) 
		&& str[i] != ' ')
		len++;
	eof = malloc((len + 1) * sizeof(char));
	if (!eof)
		exit (1);
	ft_memcpy(eof, str, len);	
	eof[len] = '\0';
	return (eof);
	
}

static char	*get_delim(char **tab, int nb)
{
	int		i;

	i = -1;
	while (tab[nb][++i] != '<')
		;	
	while (tab[nb][++i] == '<')
		;
	while ((tab[nb][i] > 8 && tab[nb][i] < 14 && tab[nb][i]) || tab[nb][i] == ' ')
		i++;
	if (tab[nb][i])
		return (get_delim_bis(tab[nb] + i));
	else
		return (get_delim_bis(tab[nb + 1]));
}

static char	*construct_heredoc(char *eof, t_data *data)
{
	int		fd;
	char	*line;
	char	*name;

	data->count_here++;
	name = ft_strjoin_free_s2("heredoc", ft_itoa((int)data->count_here));
	if (!name)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, (void *)name);
	fd = open((const char *)name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror_exit("Error opening temp file", 1, data);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, eof) == 0 && (free(line), 1))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (name);
}

static void	handle_heredoc_bis(t_data *data, char **tab, int i, t_execs *exec)
{
	char	*eof;
	
	if (data->count_here > 15)
			err_rd("bash: too many open files\n", data);
	eof = get_delim(tab, i);
	add_ptr(data->trash, eof);
	exec->infile = construct_heredoc(eof, data);
}


void	handle_heredoc(t_data *data, t_execs *exec)
{
	int		i;
	char	**tab;

	tab = exec->tokens;
	i = -1;
	while (tab[++i])
	{
		if (is_heredoc(tab[i]))
		{
			if (last_chara(tab[i], '<') && (!tab[i + 1] || !tab[i + 1][0]))
				err_rd("bash: syntax error near unexpected token `newline'\n",\
					data);
			else if (last_chara(tab[i], '<') == 1 && \
			checker_redirect_in(tab[i + 1], data, false) == 1)
				return ;
			else if (checker_redirect_in(tab[i] + 2, data, true) == 1)
				return ;
			else
				handle_heredoc_bis(data, tab, i, exec);
		}
		else if (is_input_heredoc(tab[i]))
			input_heredoc(data, exec, tab + i);
	}
}
