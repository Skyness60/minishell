/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:18:42 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/16 12:52:53 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (g_exit_signal == 0)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_signal = 130;
	}
	else if (signal == SIGQUIT && g_exit_signal == 1)
	{
		write(STDOUT_FILENO, "^'\'Quit (core dumped)", 21);
		write(STDOUT_FILENO, "\n", 1);
		g_exit_signal = 131;
	}
}

void	change_signals(bool	exec)
{
	if (exec)
	{
		g_exit_signal = 1;
		signal(SIGINT, ft_signal);
		signal(SIGQUIT, ft_signal);
	}
	else
	{
		signal(SIGINT, ft_signal);
		signal(SIGQUIT, ft_signal);
	}
}
