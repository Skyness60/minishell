/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:06:27 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/25 14:26:54 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_delim(char *input)
{
	char	*eof;
	size_t	len;
	
	len = 0;
	while ((*input && *input > 8 && *input < 14) || *input == ' ')
		input++;
	while (*input && (*input < 8 || *input > 14) && *input != ' ')
	{
		len++;
		input++;
	}
	eof = malloc((len + 1) * sizeof(char));
	if (!eof)
		perror_exit("Error w/ malloc\n", 2);
	ft_memcpy(eof, input - len, len);	
	eof[len] = '\0';
	return (eof);
}

void	handle_heredoc(t_data *data)
{
	int		i;
	char	*eof;
	char	*line;
	int		fd;

	i = -1;
	while (data->input[++i] == '<')
		;
	if (i != 2)
		return ;
	eof = get_delim(data->input + 2);
	add_ptr(data->trash, eof);
	fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror_exit("Error opening temp file", 1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}
