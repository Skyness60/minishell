/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:00 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/12 11:15:00 by sperron          ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>

#include <readline/readline.h>
#include <readline/history.h>

# define MS_NAME "bash"
#define PATH_MAX 4096

//https://git-scm.com/book/fr/v2/Commandes-Git-Cr%C3%A9ation-de-branches-et-fusion
//pour les manips git

typedef struct s_data
{
	int		in_fd;
	int		out_fd;
	int		ac;
	char	**env;
	char	**av;
	char	*prompt;
	char	*input;
	char	**paths;
}	t_data;

typedef struct s_cmd
{
	char	*name;
	int		(*cmd_fct)(t_data *data);
}	t_cmd;


//initialisation
void	prepare_data(t_data *data, char **env);

//utils
void	free_tab(char **tab);
char	**split_if_quote(char *str, char c);
void	perror_exit(char *str, int exit_code);

//signals
void	ft_signal(int signal);

//parsing
char	*create_prompt(char **env);

//core
// int		main(int argc, char **argv, char **env);
void	core_loop(t_data *data);
void	set_input(t_data *data);

// exec

void	parse_input(t_data *data);
int		count_pipes(char *str);
int		execute_cmd(t_data *data, char **cmds, int in_fd, int out_fd);
void	execute_pipes(t_data *data, char **pipes, int nb_parts);
int		is_builtin(t_data *data, int fd);
int		pwd(int	av_count);
void	set_pwd();
int		echo(char **av, int ac, int fd);
int		cd (char **args, int args_count);
int		env(t_data *data, int fd);
int		unset(t_data *data, char **args);
#endif
