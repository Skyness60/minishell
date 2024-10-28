/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:54:18 by sperron           #+#    #+#             */
/*   Updated: 2024/10/28 16:44:00 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "split_if_quote/split_with_quotes.h"
# include "./libft/libft.h"
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
# include <sys/stat.h>

# define MS_NAME "bash"
# define ERR_OPTIONS_HISTORY "invalid option\n history: usage: history [-c] \
[-d offset] [n] or history -anrw [filename] or history -ps arg [arg...]"
# define PATH_MAX 4096

typedef struct s_signals
{
	int		signal_status;
	bool	other_minish;
}	t_signals;

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
	int		(*handler)(t_data *, char **, bool, int);
}	t_cmd;

typedef struct s_history
{
	char	**save;
	size_t	count;
	size_t	capacite;
}	t_history;

typedef struct s_data	t_data;

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
	t_data			*g_data;
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
	int				cmd_exit_status;
}	t_data;

//initialisation
void	prepare_data(t_data *data, char **env);

//utils
void	free_tab(char **tab);
void	perror_exit(char *str, int exit_code, t_data *data);
size_t	array_len(char **arr);
char	**get_paths(char **env);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	free_history(t_data *history);
bool	last_chara(char *str);
char	**ft_realloc_char(char **ptr, size_t old_size, size_t new_size);
t_execs	*find_last(t_execs *first);
char	*ft_strjoin_free_s2(char *s1, char *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);
bool	is_file(char *str);
t_execs	*find_x_node(t_execs *first, int x);
void	add_infile(t_data *data, char *name);
void	check_infiles(t_data *data);
void	get_args(t_data *data, t_execs *exec);
void	destroy_heredoc(void);
int		is_fd_assigned_to_dev_null(int fd);
char	*get_var_in_env(char **env, char *var, t_data *data);
size_t	size_struct(t_execs *first);
bool	syntax_error(char *str);
char	*input_heredoc(t_data *data, char *eof);
bool	checker_redirect_in(char *str, t_data *data);
bool	checker_redirect_out(char *str, t_data *data);
bool	is_in_quotes(char *str, int pos);
bool	redirs_in_str(char *str);

//signals
void	handle_signals(bool exec, bool heredoc);

//parsing
void	set_input(t_data *data);
char	*create_prompt(void);
int		redirect_infile(t_data *data, t_execs *exec, char *name_of,
			int count);
int		redirect_outfile(t_execs *exec, char	*name_of, t_data *data,
			int count);
char	*get_name_of(char *str, t_data *data);
int		is_valid_identifier(char *arg);
int		error_env(t_data *data, char **args, char *full_paths, int fd);
int		not_event(char *str);
bool	is_in_doublequotes(char *str, int pos);
int		redirect_bis(t_data *data, t_execs *exec, int i);
char	*get_uid(void);
char	*extract_var_name(char *var, t_data *data);
int		count_backslashes_pos(char *str, int pos);
bool	big_conditions(char *str, int i);
bool	is_valid_character(char c);
char	*loop_process_backslashes(char *result, char *str, int *i, int *j);
char	*process_backslashes(t_data *data, char *str);
char	*handle_exit_code(char *str, int a, t_data *data);
char	*replace_in_str(t_data *data, char *str, char *env_value, int i);
int		handle_heredoc(t_data *data, t_execs *exec, char *eof, int count);
int		just_space(char *str);
void	renew_env(t_data *data, char *name, size_t size);
int		middle_cmd(t_ppx **ppx, int i, char **envp, char **av);
int		redirect(t_data *data, t_execs *exec);
void	err_rd(char *str, t_data *data);
char	**copy_env(char **env);
void	free_evolution(t_data *data);
char	*replace_var(char *str, t_data *data);
bool	ctrl_redir_space(char **tab, t_data *data);

//core
void	core_loop(t_data *data, char **env);
void	reset_struct(t_data *data);

// wait
void	waitfunction(t_data *data);

// exec

void	parse_input(t_data *data);
int		update_env(t_data *data, char *var);
char	**ft_realloc_char(char **ptr, size_t old_size, size_t new_size);
void	execute_cmds(t_data *data, t_execs *cmds, int (*pipe_fd)[2]);
void	get_infile(int in_fd, t_execs *cmds, int (*pipe_fd)[2], bool tan[2]);
void	get_outfile(int out_fd, t_execs *cmds, int (*pipe_fd)[2], bool tab[2]);
void	get_redirect(t_data *data, t_execs *cmds, int (*pipe_fd)[2]);
void	ft_exec_infile(char *path, char **cmds, t_ppx *ppx, char *cmd);
void	ft_exec_outfile(char *path, char **cmds, t_ppx *ppx, char *cmd);
void	exec_child_first(t_ppx *ppx, char *cmd, char *file);
void	close_fds_out(int (*pipe_fd)[2], int nb_pipes, int index);
void	exec_child_last(t_ppx *ppx, char *cmd, char *file, bool heredoc);
void	exec_child_midle(t_ppx *ppx, char *cmd);
int		ft_execvp(t_data *data, t_execs *cmds);
int		is_builtin(t_data *data, int fd, t_execs *cmds, bool is_child);
bool	check_builtins_env(t_execs *cmds);
char	**find_paths(char **envp);
int		is_valid_identifier(char *arg);
int		ft_arglen(char *str);
int		ft_valuelen(char *str);
int		export_error(char *argv, int status, bool is_child);
int		add_var(char *args_without_value, char *args, t_data *data);
void	add_export(t_data *data, char *args);
char	*find_path(char **paths, t_execs *cmd);
void	set_cmd(t_data *data);
int		handle_echo(t_data *data, char **args, bool is_child, int fd);
int		handle_cd(t_data *data, char **args, bool is_child, int fd);
int		handle_pwd(t_data *data, char **args, bool is_child, int fd);
int		handle_export(t_data *data, char **args, bool is_child, int fd);
int		handle_unset(t_data *data, char **args, bool is_child, int fd);
int		handle_env(t_data *data, char **args, bool is_child, int fd);
int		handle_history(t_data *data, char **args, bool is_child, int fd);
int		handle_exit(t_data *data, char **args, bool is_child, int fd);	
char	*ft_getenv(char **env, char *name);
void	set_pwd(t_data *data);

// pipes
int		pipeslines(t_data *data, t_execs **execs, int i);

// garbage collecor

void	init_garbage_collector(t_garb_c *trash);
void	add_ptr(t_garb_c *trash, void *ptr);
void	add_ptr_tab(t_garb_c *trash, void **ptr_arr, int arr_len, \
bool is_malloced);
void	free_all(t_garb_c *trash);

extern t_signals		g_signals;
#endif
