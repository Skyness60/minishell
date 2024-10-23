/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:18:42 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/23 10:52:45 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_signal_in_exec(int signal)
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

static int	ft_nothing()
{
	return (0);
}

static void	ft_signal_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		rl_event_hook = ft_nothing;
		destroy_heredoc();
		g_signal.signal_status = 130;
		rl_done = 1;
	}
}

static void	ft_signal_prompt(int signal)
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

void	handle_signals(bool exec, bool heredoc)
{
	rl_event_hook = ft_nothing;
	if (exec)
	{
		signal(SIGINT, ft_signal_in_exec);
		signal(SIGQUIT, ft_signal_in_exec);
	}
	else if (heredoc)
	{
		signal(SIGINT, ft_signal_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, ft_signal_prompt);
		signal (SIGQUIT, SIG_IGN);
	}
}
