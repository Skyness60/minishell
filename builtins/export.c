/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/17 16:37:12 by jlebard          ###   ########.fr       */
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

	args = split_with_quotes("sort ", " \t\n\v\f");
	add_ptr_tab(data->trash, (void **)args, array_len(args), true);
	dup2(fd[0], 0);
	dup2(out, 1);
	close(fd[0]);
	close(fd[1]);
	ft_execvp(data, (data->pipes_to_ex[0]));
}

static int	sort_export(t_data *data, int out)
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

int	handle_export(t_data *data, char **args, int ac, int fd)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	if (ac == 0)
		return (sort_export(data, fd));
	else
	{
		while (args[i] != NULL)
		{
			if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
				out = export_error(args[i]);
			else if (ft_str_alnum(args[i]))
				out = export_error(args[i]);
			else if (ft_strchr(args[i], '='))
				putenv(args[i]);
			i++;
		}
	}
	return (out);
}
