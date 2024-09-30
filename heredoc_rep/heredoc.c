/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:06:27 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/30 13:01:02 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strjoin_free2(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[j])
	{
		dest[i] = s2[j++];
		i++;
	}
	free(s2);
	dest[i] = '\0';
	return (dest);
}

static char	*get_delim(char *input)
{
	char	*eof;
	size_t	len;
	
	len = 0;
	while ((*input && *input > 8 && *input < 14) || *input == ' ' && *input)
		input++;
	if (*input == '\0')
		return (NULL);
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

static int	count_heredoc(char *input)
{
	int	count;
	
	count = 0;
	while (*input)
	{
		if (*input == '<' && *(input + 1) == '<' && *(input + 2) != '<')
			count++;
		input++;
	}
	return (count);
}

static void	handle_heredoc_bis(char *eof, t_data *data, int count)
{
	int		fd;
	char	*line;
	char	*name;
	
	name = ft_strjoin_free2("heredoc", ft_itoa(count));
	if (!name)
		perror_exit("Error w/ malloc\n", 2);
	fd = open(ft_strjoin("heredoc", ft_itoa(count)), \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror_exit("Error opening temp file", 1);
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
}

void	handle_heredoc(t_data *data)
{
	int		i;
	int		count;
	char	*eof;
	char	*line;

	i = -1;
	count = count_heredoc(data->input);
	if (count > 16)
		return (write(2, "bash: too many open files", 26), NULL);
	count = 0;
	while (data->input[++i])
	{
		if (data->input[i] == '<' && data->input[i + 1] == '<' && \
			data->input[i + 2] != '<')
		{
			eof = get_delim(data->input + 2);
			if (eof == NULL)
				return ;
			add_ptr(data->trash, eof);
			count++;
		}
	}
}
