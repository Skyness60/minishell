/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:00 by jlebard           #+#    #+#             */
/*   Updated: 2024/08/29 15:14:58 by jlebard          ###   ########.fr       */
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
	char	*input;
	char	**paths;
}	t_data;


//initialisation
void	prepare_data(t_data *data, char **env);

//utils
void	free_tab(char **tab);

//signals
void	ft_signal(int signal);

//parsing
char	*create_prompt(char **env);

//core
int		main(int argc, char **argv, char **env);
void	core_loop(t_data *data);
void	set_input(t_data *data);

#endif