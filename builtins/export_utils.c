/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/14 15:26:01 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_data *data, int fd[2])
{
	int	i;
	int	j;

	i = 0;
	dup2(fd[1], 1);
	while (data->env[i])
	{
		if (data->env[i][0] == '?' || data->env[i][0] == '-')
		{
			i++;
			continue ;
		}
		j = 0;
		printf("declare -x ");
		while (data->env[i][j] != '=' && data->env[i][j])
			printf("%c", data->env[i][j++]);
		printf("=\"%s\"\n", ft_strchr(data->env[i], '=') + 1);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

void	sort_it(t_data *data, int fd[2], int out)
{
	char	**args;

	args = split_with_quotes("sort ", " \t\n\v\f");
	add_ptr_tab(data->trash, (void **)args, array_len(args), true);
	dup2(fd[0], 0);
	dup2(out, 1);
	close(fd[0]);
	close(fd[1]);
	ft_execvp(data, (data->pipes_to_ex[0]));
}



int	sort_export(t_data *data, int out)
{
	int		fd[2];
	int		pid;
	int		id;

	if (pipe(fd) == -1)
		return (perror_exit("FATAL ERROR", 1, data), 1);
	pid = fork();
	if (pid < 0)
		return (perror_exit("FATAL ERROR", 1, data), 1);
	if (pid == 0)
		print_export(data, fd);
	else
	{
		waitpid(pid, NULL, 0);
		id = fork();
		if (id < 0)
			return (perror_exit("FATAL ERROR", 1, data), 1);
		if (id == 0)
			sort_it(data, fd, out);
		close(fd[0]);
		close(fd[1]);
		waitpid(id, NULL, 0);
	}
	return (0);
}
int update_env(t_data *data, char *var)
{
    int j;

	j = 0;
    while (data->env[j])
	{
        if (strncmp(data->env[j], var, strchr(var, '=') - var) == 0)
		{
            free(data->env[j]);
            data->env[j] = var;
            return (1);
        }
        j++;
    }
    return (0);
}

char	**ft_realloc_char(char **ptr, size_t old_size, size_t new_size)
{
	char	**dest;
	size_t	i;
	
	i = -1;
	if (ptr == NULL)
		return (malloc(new_size));
	dest = malloc(new_size);
	while (++i < (old_size / sizeof(char *)))
	{
		dest[i] = ft_strdup(ptr[i]);
		free(ptr[i]);
	}
	free(ptr);
	return (dest);
}
