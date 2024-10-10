/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:58:59 by sperron           #+#    #+#             */
/*   Updated: 2024/10/10 08:48:27 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPX_H
# define PPX_H
# include "../minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_execs	t_execs;
typedef struct s_data	t_data;


int		file_to_pipe(t_data *data, t_execs *execs);
#endif // !PPX_H