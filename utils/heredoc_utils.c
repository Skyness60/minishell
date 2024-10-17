/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:39:50 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/17 16:40:51 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	input_heredoc_bis(t_data *data, t_execs *exec, char **tab)
{
	int		fd;
	char	*name;
	
	name = ft_strjoin_free_s2("heredoc", ft_itoa((int)data->count_here));
	if (!name)
		perror_exit("Error w/ malloc\n", 2, data);
	add_ptr(data->trash, (void *)name);
	fd = open((const char *)name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		perror_exit("Error opening temp file", 1, data);
	if (last_chara(*tab, '<'))
	{
		write(fd, tab[1], ft_strlen(tab[1]));
		write(fd, "\n", 1);
	}
	else
	{
		write(fd, tab[0] + 3, ft_strlen(tab[0]) - 3);
		write(fd, "\n", 1);
	}
	exec->infile = name;
}

void	input_heredoc(t_data *data, t_execs *exec, char **tab)
{
	data->count_here++;
	if (data->count_here > 15)
		return (err_rd("bash: too many open files\n", data));
	if (!tab[0][3] && !tab[1])
		return err_rd("bash: syntax error near unexpected token `newline'\n" \
			, data);
	if (last_chara(*tab, '<') == 1 && \
		checker_redirect_in(tab[1], data, false) == 1)
		return ;
	else if (checker_redirect_in(*tab + 3, data, true) == 1)
		return ;
	input_heredoc_bis(data, exec, tab);
}

bool	is_input_heredoc(char *str)
{
	int	i;

	i = -1;
	if (ft_strlen(str) < 3)
		return (false);	
	while (str[++i])
	{
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<' && str[i + 2] &&\
			str[i + 2] == '<')
			return (true);
	}
	return (false);
}

bool	is_heredoc(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && (str[i + 2] != '<' \
			|| !str[i + 2]))
			return (true);
		else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] &&\
			str[i + 2] == '<')
			return (false);
	}
	return (false);
}

void	destroy_herdoc()
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
