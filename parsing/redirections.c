/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:52:06 by jlebard           #+#    #+#             */
/*   Updated: 2024/11/07 10:40:17 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_infile(t_data *data, t_execs *exec, char *name_of,
				int count)
{
	char	*err_msg;

	if (count == 1)
	{
		if (access(name_of, F_OK) == -1)
		{
			err_msg = ft_strjoin("bash: ", name_of);
			err_msg = ft_strjoin_free_s1(err_msg, \
			": No such file or directory\n");
			err_rd(err_msg, data);
			return (free(err_msg), 0);
		}
		exec->infile = name_of;
		return ((int)ft_strlen(name_of) + count - 1);
	}
	else if (count >= 2)
		return (handle_heredoc(data, exec, name_of, count));
	return (0);
}

int	redirect_outfile(t_execs *exec, char *name_of, t_data *data,
					int count)
{
	int		fd;

	if (count == 1)
	{
		exec->tronque = 1;
		fd = open(name_of, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1 && name_of[0] != 0)
			return (perror("bash: "), 1);
		if (data->out_fd != 1)
			close (data->out_fd);
		data->out_fd = fd;
		exec->outfile = name_of;
	}
	else if (count == 2)
	{
		fd = open(name_of, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1 && name_of[0] != 0)
			return (perror("bash: "), 1);
		if (data->out_fd != 1)
			close (data->out_fd);
		data->out_fd = fd;
		exec->outfile = name_of;
		exec->tronque = 0;
	}
	return ((int)ft_strlen(name_of) + count - 1);
}

int	redirect(t_data *data, t_execs *exec)
{
	int	i;

	i = -1;
	while (data->error == false && exec->tokens[++i])
	{
		if (ignore_redir(data, exec, i) == 1)
			continue ;
		if (checker_redirect_in(exec->tokens[i], data) == 1 || \
			checker_redirect_out(exec->tokens[i], data) == 1)
			if (redirect_bis(data, exec, i) == 1)
				return (1);
	}
	return (0);
}
