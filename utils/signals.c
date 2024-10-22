/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:18:42 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/22 17:15:17 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signal_in_exec(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (signal == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit (core dumped)", 21);
		write(STDOUT_FILENO, "\n", 1);
		g_signal.signal_status = 131;
	}
}

void	ft_signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		destroy_heredoc();
		g_signal.signal_status = 130;
		// dup2(g_signal.stdin, STDIN_FILENO);
		write (1, "\n", 1);
		rl_done = 1;
		rl_replace_line(g_signal.eof, 0);
		// close(g_signal.stdin);
	}
}

void	ft_signal_outside(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal.signal_status = 130;
	}
}
