/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:42:03 by sperron           #+#    #+#             */
/*   Updated: 2024/10/24 10:56:37 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_child_process(int pipefd[2])
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	execve("/usr/bin/id", (char *[]){"id", "-u", NULL}, NULL);
	perror("execve");
	exit(1);
}

char	*exec_parent_process(int pipefd[2], char *uid)
{
	int	i;

	close(pipefd[1]);
	wait(NULL);
	read(pipefd[0], uid, 15);
	uid[15] = '\0';
	i = 0;
	while (uid[i] != '\0')
	{
		if (uid[i] == '\n')
		{
			uid[i] = '\0';
			break;
		}
		i++;
	}
	close(pipefd[0]);
	return (uid);
}
char	*get_uid(void)
{
	int		pipefd[2];
	pid_t	pid;
	char	*uid;

	uid = malloc(16);
	if (!uid)
	{
		perror("malloc");
		return (NULL);
	}
	if (pipe(pipefd) == -1)
		return (perror("pipe"), NULL);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), NULL);
	if (pid == 0)
		exec_child_process(pipefd);
	else
		return (exec_parent_process(pipefd, uid));
	return (uid);
}

char	*extract_var_name(char *var, t_data *data)
{
	int		len;
	char	*var_name;

	len = 0;
	if (!ft_isalpha(var[len]) && ft_isdigit(var[len]))
		return (ft_substr(var, 1, ft_strlen(var)));
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	var_name = ft_substr(var, 0, len);
	if (!var_name)
		perror_exit("Error w/ malloc\n", 2, data);
	return (var_name);
}