/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 12:28:04 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int	export_error(char *argv)
{
	write(2, "bash: export: '", 16);
	write(2, argv, ft_strlen(argv));
	write(2, "' :not a valid identifier\n", 27);
	return (1);
}

static void	print_export(t_data *data, int fd[2])
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

static void	sort_it(t_data *data, int fd[2], int out)
{
	char	**args;
	char	*paths;

	args = split_if_quote("sort ", ' ');
	paths = find_path(data->paths, args[0]);
	dup2(fd[0], 0);
	dup2(out, 1);
	close(fd[0]);
	close(fd[1]);
	execve(paths, args, data->env);
	ft_execvp("sort", args);
}

static int	sort_export(t_data *data, int out)
{
	int		fd[2];
	int		pid;
	int		id;

	if (pipe(fd) == -1)
		return (return_error("FATAL ERROR", 1));
	pid = fork();
	if (pid < 0)
		return (return_error("FATAL ERROR", 1));
	if (pid == 0)
		print_export(fd);
	else
	{
		waitpid(pid, NULL, 0);
		id = fork();
		if (id < 0)
			return (return_error("FATAL ERROR", 1));
		if (id == 0)
			sort_it(fd, out);
		close(fd[0]);
		close(fd[1]);
		waitpid(id, NULL, 0);
	}
	return (0);
}

int	export_comand(t_data *data, char **args, int argc, int fd)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	if (argc == 0)
		return (sort_export(data, fd));
	else
	{
		while (args[i] != NULL)
		{
			if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
				out = export_error(args[i]);
			else if (str_alnum(args[i]))
				out = export_error(args[i]);
			else if (ft_strchr(args[i], '='))
				ft_putenv(args[i]); //ft_putenv
			i++;
		}
	}
	return (out);
}