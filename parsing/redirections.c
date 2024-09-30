/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:12:08 by jlebard           #+#    #+#             */
/*   Updated: 2024/09/30 13:19:09 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[j])
	{
		dest[i] = s2[j++];
		i++;
	}
	free(s1);
	dest[i] = '\0';
	return (dest);
}

static bool	error_redirect(char *cmd)
{
	int	count;

	count = 0;
	if (*(cmd + 1) != '>')
		return (false);
	while (*cmd && *cmd == '>')
	{
		cmd++;
		count++;
	}
	if (count > 3)
		write (2, "bash: syntax error near unexpected token `>>'", 46);
	else if (count == 3)
		write (2, "bash: syntax error near unexpected token `>'", 45);
	return (true);
}

static char	*redirect_infile(char *cmd, int nb, t_data *data)
{
	char	*temp;
	char	*temp2;
	char	*dest;
	int		i;

	i = -1;
	temp = ft_strdup(cmd + nb + 1);
	if (!temp)
		perror_exit("Error w/ malloc\n", 2);
	while (ft_isspace(temp[++i]) == 1)
		;
	temp2 = ft_strndup(cmd, nb);
	if (!temp2)
		perror_exit("Error w/ malloc\n", 2);
	dest = ft_strjoin(ft_strjoin_free(temp, " "), temp2);
	free(temp2);
	add_ptr(data->trash, dest);
	return (dest);
}


static char	*redirect_outfile(char *cmd, int nb, t_data *data)
{
	char	*temp;
	char	*temp2;
	int		i;
	char	*dest;

	if (error_redirect(cmd + nb) == 1)
		return (NULL);
	i = -1;
	temp = ft_strdup(cmd + nb + 1);
	if (!temp)
		perror_exit("Error w/ malloc\n", 2);
	while (ft_isspace(temp[++i]) == 1)
		;
	temp2 = ft_strndup(cmd, nb);
	if (!temp2)
		perror_exit("Error w/ malloc\n", 2);
	dest = ft_strjoin(ft_strjoin_free(temp2, " "), temp);
	free(temp);
	add_ptr(data->trash, dest);
	return (dest);
}

char	**redirect(char **pipes, t_data *data)
{
	int	i;

	i = -1;
	while ()
	{
		while (cmd[++i])
		{
			if (cmd[i] == '<')
				return (redirect_infile(cmd, i, data));
			else if (cmd[i] == '>' && cmd[i + 1])
				return (redirect_outfile(cmd, i, data));
		}
		return (cmd);
	}
}
