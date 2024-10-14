/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:15:00 by jlebard           #+#    #+#             */
/*   Updated: 2024/10/14 13:07:40 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "split_if_quote/split_with_quotes.h"
# include "./libft/libft.h"
# include "ppx/ppx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

# define MS_NAME "bash"
# define ERR_OPTIONS_HISTORY "invalid option\n history: usage: history [-c] \
[-d offset] [n] or history -anrw [filename] or history -ps arg [arg...]"
# define PATH_MAX 4096

//https://git-scm.com/book/fr/v2/Commandes-Git-Cr%C3%A9ation-de-branches-et-fusion
//pour les manips git
typedef struct s_data	t_data;

typedef struct s_ppx	t_ppx;

typedef struct s_garbage_c
{
	void	**ptr_arr;
	size_t	capacite;
	size_t	count;
}	t_garb_c;

typedef struct s_cmd
{
	char	*name;
	int		(*handler)(t_data *, char **, int, int);
}	t_cmd;

typedef struct s_history
{
	char	**save;
	size_t	count;
	size_t	capacite;
}	t_history;

typedef struct s_execs
{	
	char			**tokens;
	char			**args;
	char			*cmd;
	char			*infile;
	char			*outfile;
	struct s_execs	*next;
	struct s_execs	*previous;
	bool			tronque;
	char			*input;
	int				index;
}	t_execs;

typedef struct s_save_infiles
{
	char	**names;
	size_t	count;
	size_t	capacity;
}	t_save_infiles;

typedef struct s_data
{
	bool			error;
	int				in_fd;
	int				out_fd;
	int				ac;
	int				start;
	char			**env;
	char			*prompt;
	char			*input;
	t_save_infiles	*save_infiles;
	char			**paths;
	size_t			count_here;
	t_execs			**pipes_to_ex;
	t_garb_c		*trash;
	t_cmd			*cmds;
	t_history		*history;
	int				nb_execs;
}	t_data;

//initialisation
void	prepare_data(t_data *data, char **env);

//utils
void	free_tab(char **tab);
void	perror_exit(char *str, int exit_ccode);
size_t	array_len(char **arr);
char	**get_paths(char **env);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	free_history(t_data *history);
bool	last_chara(char *str, char c);
t_execs	*find_last(t_execs *first);
char	*ft_strjoin_free_s2(char *s1, char *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);
bool	is_heredoc(char *str);
t_execs *find_x_node(t_execs *first, int x);
void	add_infile(t_data *data, char *name);
void	check_infiles(t_data *data);
void	get_args(t_data *data, t_execs *exec);
void	destroy_herdoc();
char	*get_var_in_env(char **env, char *var, t_data *data);
size_t    size_struct(t_execs *first);

//signals
void	ft_signal(int signal);

//parsing
void	set_input(t_data *data);
char	*create_prompt(char **env, t_data *data);
void	handle_heredoc(t_data *data, t_execs *exec);
int		just_space(char *str);
int		middle_cmd(t_ppx **ppx, int i, char **envp, char **av);
void	redirect(t_data *data, t_execs *exec);
void	err_rd(char *str, t_data *data);
void	get_cmd(t_data *data, t_execs *exec);
char	**copy_env(char **env);

//core
void	core_loop(t_data *data, char **env);

// exec

void	parse_input(t_data *data);
int		execute_one_cmd(t_data *data, t_execs **cmds);
int		get_redirect_and_builtins(int in_fd, int *out_fd, t_execs *cmds);
void	get_infile(int in_fd, t_execs *cmds, int pipe_fd[2]);
void	get_outfile(int out_fd, t_execs *cmds, int pipe_fd[2]);
void	get_redirect_and_exec(int in_fd, int out_fd, t_execs *cmds, int pipe_fd[2]);
void	ft_exec_infile(char *path, char **cmds, t_ppx *ppx, char *cmd);
void	ft_exec_outfile(char *path, char **cmds, t_ppx *ppx, char *cmd);
void	exec_child_first(t_ppx *ppx, char *cmd, char *file);
void	exec_child_last(t_ppx *ppx, char *cmd, char *file, bool heredoc);
void	exec_child_midle(t_ppx *ppx, char *cmd);
int		ft_execvp(t_data *data, t_execs *cmds);
int		is_builtin(t_data *data, int fd, t_execs *cmds);
bool	check_builtins(t_data *data, t_execs *cmds);
char	**find_paths(char **envp);
char	*find_path(char **paths, t_execs *cmd);
void	set_cmd(t_data *data);
int		handle_echo(t_data *data, char **args, int arg_count, int fd);
int		handle_cd(t_data *data, char **args, int arg_count, int fd);
int		handle_pwd(t_data *data, char **args, int arg_count, int fd);
int		handle_export(t_data *data, char **args, int arg_count, int fd);
int		handle_unset(t_data *data, char **args, int arg_count, int fd);
int		handle_env(t_data *data, char **args, int arg_count, int fd);
int		handle_history(t_data *data, char **args, int ac, int fd);
char	*ft_getenv(char **env, char *name);
void	set_pwd(t_data *data);

// pipes
int	pipeslines(t_data *data, t_execs **execs);

// garbage collecor

void	init_garbage_collector(t_garb_c *trash);
void	add_ptr(t_garb_c *trash, void *ptr);
void	add_ptr_tab(t_garb_c *trash, void **ptr_arr, int arr_len, \
bool 	is_malloced);
void	free_all(t_garb_c *trash);

#endif
