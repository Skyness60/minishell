/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:47:57 by sperron           #+#    #+#             */
/*   Updated: 2024/10/28 12:45:58 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_in_quotes(char *str, int pos)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < pos)
		if (str[i] == '\'')
			count++;
	if (count % 2 == 1)
		return (true);
	else
		return (false);
}

static char	*delete_dollar(t_data *data, char *str, int size_d, int k)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = -1;
	dest = malloc((k + ft_strlen(str + k + size_d) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < k)
	{
		dest[++j] = str[i];
		i++;
	}
	while (str[i + size_d])
		dest[++j] = str[i++ + size_d];
	dest[j + 1] = '\0';
	if (dest[0] == '\0')
		add_ptr(data->trash, dest);
	return (dest);
}

char	*handle_exit_code(char *str, int a, t_data *data)
{
	int		i;
	int		j;
	int		k;
	char	*dest;
	char	*exit_code;

	exit_code = ft_itoa(data->cmd_exit_status);
	if (!exit_code)
		return (NULL);
	i = a;
	dest = malloc(i + ft_strlen(exit_code) + ft_strlen(str + i + 2) + 1);
	if (!dest)
		return (NULL);
	j = i;
	ft_memcpy(dest, str, i);
	k = -1;
	while (exit_code[++k])
		dest[j++] = exit_code[k];
	i += 2;
	while (str[i] != '\0')
		dest[j++] = str[i++];
	return (dest[j] = '\0', free(exit_code), dest);
}

char	*replace_in_str(t_data *data, char *str, char *env_value, int i)
{
	int		size_d;
	char	*dest;
	int		len_arg;
	int		j;
	int		k;

	len_arg = i;
	size_d = 0;
	while (is_valid_character(str[++len_arg]))
		size_d++;
	k = -1;
	if (!env_value)
		return (delete_dollar(data, str, size_d + 1, i));
	dest = malloc(i + ft_strlen(env_value) + 2 + ft_strlen(str + len_arg) + 1);
	if (!dest)
		return (NULL);
	j = -1;
	while (++j < i)
		dest[++k] = str[j];
	j = -1;
	while (env_value[++j])
		dest[++k] = env_value[j];
	while (str[len_arg])
		dest[++k] = str[len_arg++];
	return (dest[k + 1] = '\0', dest);
}

bool	is_valid_character(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '*')
		return (true);
	else
		return (false);
}
