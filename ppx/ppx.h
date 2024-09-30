/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:58:59 by sperron           #+#    #+#             */
/*   Updated: 2024/09/26 11:28:37 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPX_H
# define PPX_H
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_ppx
{
	int				pipe_fd[2];
	char			**paths;
	char			**envp;
	struct s_ppx	*next;
	struct s_ppx	*prev;
}					t_ppx;

typedef enum e_error_code
{
	ERR_FILE_NOT_FOUND,
	ERR_ARGS,
	ERR_PERMISSION_DENIED,
	ERR_CMD_NOT_FOUND,
	ERR_PIPE_FAILURE,
	ERR_FORK_FAILURE,
	ERR_HEREDOC,
	ERR_UNKNOWN
}				t_error_code;

void	ppx_del(t_ppx **ppx);
int		ppx_error(t_error_code code, char **av, int ac, char *cmd);
t_ppx	*ppx_new(char **envp);
int		ppx_add_back(t_ppx **ppx, t_ppx *ppx_new);
void	ft_free_strs(char **strs);
int	file_to_pipe(char *file, t_ppx *ppx);
int	pipe_to_file(char *file, t_ppx *ppx, bool heredoc);
void	pipe_to_pipe(int pipe_fd_1[2], int pipe_fd_2[2], t_ppx *ppx);

#endif // !PPX_H