/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:00 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/16 11:41:09 by sperron          ###   ########.fr       */
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
typedef struct s_data t_data; 

typedef struct s_garbage_c
{
	void	**ptr_arr;
	size_t	count;
}	t_garb_c;

typedef struct s_cmd
{
    char *name;
    int (*handler)(t_data *, char **, int, int);
} t_cmd;


typedef struct s_data
{
	int			in_fd;
	int			out_fd;
	int			ac;
	char		**env;
	char		**av;
	char		*prompt;
	char		*input;
	char		**paths;
	t_garb_c	*trash;
	t_cmd		*cmds;
}	t_data;




//initialisation
void	prepare_data(t_data *data, char **env);

//utils
void	free_tab(char **tab);
char	**split_if_quote(char *str, char c);
void	perror_exit(char *str, int exit_code);
int		array_len(char **arr);
char	**get_paths(char **env);

//signals
void	ft_signal(int signal);

//parsing
char	*create_prompt(char **env, t_data *data);

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
int		ft_execvp(t_data *data, char **cmds);
int		is_builtin(t_data *data, int fd);
char	**find_paths(char **envp);
char	*find_path(char **paths, char *cmd);
void	set_cmd(t_data *data);
int handle_echo(t_data *data, char **args, int arg_count, int fd);
int handle_cd(t_data *data, char **args, int arg_count, int fd);
int handle_pwd(t_data *data, char **args, int arg_count, int fd);
int handle_export(t_data *data, char **args, int arg_count, int fd);
int handle_unset(t_data *data, char **args, int arg_count, int fd);
int handle_env(t_data *data, char **args, int arg_count, int fd);
void	set_pwd();

// garbage collecor

void	init_garbage_collector(t_garb_c *trash);
void	add_ptr(t_garb_c *trash, void *ptr);
void	add_ptr_tab(t_garb_c *trash, void **ptr_arr, int arr_len);
void	free_all(t_garb_c *trash);


#endif
