/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:11:12 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 12:45:59 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_error(char *argv)
{
	write(2, "bash: unset: '", 15);
	write(2, argv, ft_strlen(argv));
	write(2, "' :not a valid identifier\n", 27);
	return (1);
}

void	unset_one(t_data *data, char *arg)
{
	int		length;
	char	**pointer;
	int		i;

	length = ft_strlen(arg);
	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], arg, length) && data->env[i][length] == '=')
		{
			pointer = &data->env[i];
			while (*pointer)
			{
				pointer[0] = pointer[1];
				pointer++;
			}
		}
		i++;
	}
}

int	is_string_and_number(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (!ft_isalnum(string[i]) && string[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	handle_unset(t_data *data, char **args)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	while (args[i] != NULL)
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			out = unset_error(args[i]);
		else if (is_string_and_number(args[i]))
			out = unset_error(args[i]);
		else
			unset_one(data, args[i]);
		i++;
	}
	return (out);
}