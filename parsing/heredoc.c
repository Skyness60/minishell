/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:06:27 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/27 23:58:15 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	destroy_heredoc(void)
{
	int		i;
	char	*str;
	char	*temp;

	i = 1;
	while (i < 20)
	{
		temp = ft_itoa(i);
		str = ft_strjoin("heredoc", temp);
		if (access(str, F_OK) == 0)
			unlink(str);
		free(temp);
		free(str);
		i++;
	}
}

char	*input_heredoc(t_data *data, char *eof)
{
	char	*name;
	int		fd;

	data->count_here++;
	if (data->count_here > 15)
	{
		err_rd("bash: too many open files\n", data);
		return (NULL);
	}
	name = ft_strjoin_free_s2("heredoc", ft_itoa((int)data->count_here));
	if (!name)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, (void *)name);
	fd = open((const char *)name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write (fd, eof, ft_strlen(eof));
	write (fd, "\n", 1);
	return (name);
}

static char	*construct_heredoc(char *eof, t_data *data, char *name)
{
	int		fd;
	char	*line;

	fd = open((const char *)name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror_exit("Error opening temp file\n", 1, data);
	handle_signals(0, 1);
	line = readline("> ");
	while (g_signals.signal_status != 130 && line)
	{
		if (ft_strcmp(line, eof) == 0 && (free(line), 1))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (g_signals.signal_status == 130)
		data->error = true;
	if (access(name, F_OK) != 0)
		return (NULL);
	close(fd);
	return (name);
}

int	handle_heredoc(t_data *data, t_execs *exec, char *eof, int count)
{
	int		i;
	char	*name;

	i = -1;
	if (count == 2)
	{
		data->count_here++;
		if (data->count_here > 15)
			return (err_rd("bash: too many open files\n", data), 128901);
		name = ft_strjoin_free_s2("heredoc", ft_itoa((int)data->count_here));
		add_ptr(data->trash, (void *)name);
		if (!name)
			perror_exit("Error w/ malloc\n", 2, data);
		exec->infile = construct_heredoc(eof, data, name);
	}
	else if (count == 3)
		exec->infile = input_heredoc(data, eof);
	return ((int)ft_strlen(eof) + count - 1);
}
