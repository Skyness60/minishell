/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:00 by jlebard           #+#    #+#             */
/*   Updated: 2024/08/07 16:59:15 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_data
{
	char	**env;
	char	*prompt;
}	t_data;

int		main(int argc, char **argv, char **env);
void	core_loop(t_data *data);

//initialisation
void	init_data(t_data *data, char **env);
void	set_data(t_data *data);

//utils
void	free_tab(char **tab);

//signals
void	ft_signal(int signal);

//parsing
char	*create_prompt(char **env);

#endif