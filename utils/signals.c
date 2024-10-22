/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:18:42 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/21 12:14:54 by jlebard          ###   ########.fr       */
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
		write(STDOUT_FILENO, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		g_exit_signal = 130;
	}
}

void	change_signals(bool exec)
{
	if (exec)
	{
		signal(SIGINT, ft_signal_in_exec);
		signal(SIGQUIT, ft_signal_in_exec);
	}
	else
	{
		signal(SIGINT, ft_signal_outside);
		signal(SIGQUIT, SIG_IGN);
	}
}
