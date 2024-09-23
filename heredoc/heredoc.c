/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:06:27 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/23 15:08:49 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_delim(char *input)
{
	char	*eof;
	char	*start_delim;
	size_t	delim_len;
	int		i;

	delim_len = 0;
	i = -1;
	start_delim = ft_strdup(input + 2);
	if (!start_delim)
		perror_exit("Error w/ malloc", 2);
	while (start_delim[++i] && ((start_delim[i] > 8 && start_delim[i] < 14) || \
		start_delim[i] == ' '))
		;
	while (start_delim[i] && (start_delim[i] < 8 || start_delim[i] > 14 || \
		start_delim[i] != ' '))
	{
		delim_len++;
		i++;
	}
	eof = malloc((delim_len + 1) * sizeof(char));
	if (!eof)
		perror_exit("Error w/ malloc\n", 2);
	ft_memcpy(eof, start_delim + i - (int)delim_len, delim_len);	
	eof[delim_len] = '\0';
	free(start_delim);
	return (eof);
}

static char	*get_buff(char *eof)
{
	char	*buffer;
	char	*line;
	size_t	size_of_buff;
	
	size_of_buff = 0;
	buffer = malloc(10000 * sizeof(char));
	if (!buffer)
		perror_exit("Error w/ malloc\n", 2);
	while (1)
	{
		line = readline("> ");
		if (strncmp(line, eof, ft_strlen(eof)) && line[ft_strlen(eof)] == '\n')
			break ;
		else
		{
			ft_strncat(buffer, line, ft_strlen(line));
			buffer[ft_strlen(line) + size_of_buff] = '\0';
			size_of_buff = ft_strlen(buffer);
		}
	}
	return (buffer);
}

void	handle_heredoc(t_data *data)
{
	int		i;

	i = -1;
	while (data->input[++i])
	{
		if (data->input[i] == '<' && data->input[i + 1] == '<' && \
			data->input[i + 2] != '<')
		{
			data->heredoc = get_buff(get_delim(data->input));
			if (!data->heredoc)
				perror_exit("Error w/ malloc\n", 2);
			add_ptr(data->trash, data->heredoc);
		}
	}
}
