/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:18:42 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/22 05:43:43 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_signal_in_exec(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (signal == SIGQUIT)
	{
		write(STDOUT_FILENO, "^'\'Quit (core dumped)", 21);
		write(STDOUT_FILENO, "\n", 1);
		g_exit_signal = 131;
	}
}

static void	ft_signal_outside(int signal)
{
	if (signal == SIGINT)
	{
		if (g_exit_signal == 1)
			destroy_herdoc();
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_signal = 130;
	}
}

void	change_signals(bool exec)
{
	struct sigaction act;
	
	ft_bzero((void *)&act, sizeof(sigaction));
	act.sa_flags = SA_RESTART;
	act.sa_handler = ft_signal_outside;
	if (exec)
	{
		signal(SIGINT, ft_signal_in_exec);
		signal(SIGQUIT, ft_signal_in_exec);
	}
	else
	{
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}
