/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/21 01:15:52 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_valid_identifier(char *arg)
{
    int	i;

    if (!ft_isalpha(arg[0]) && arg[0] != '_')
        return (0);
    i = 1;
    while (arg[i] && arg[i] != '=')
	{
        if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int	ft_arglen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

int	ft_valuelen(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '=')
	{
		i++;
		while (str[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	add_var(char *args_without_value, char *args, t_data *data)
{
	int		env_len;
	int		k;
	char	*result;
	char	**env_temp;

	if (is_valid_identifier(args_without_value))
    {
		k = -1;
        result = ft_strdup(args);
        if (!result)
            return (free(args_without_value), 1);
        env_len = array_len(data->env);
        env_temp = malloc((env_len + 2) * sizeof(char *));
        if (!env_temp)
            return (free(result), free(args_without_value), 1);
        if (data->env)
		{
            while (++k < env_len)
                env_temp[k] = data->env[k];	
		}
		return (env_temp[env_len] = result, env_temp[env_len + 1] = NULL, \
		free(data->env), data->env = env_temp, 0);
    }
	return (0);
}
void add_export(t_data *data, char *args)
{
    int j;
	int i;
    char *args_without_value;

	j = ft_arglen(args);
    args_without_value = malloc((j + 1) * sizeof(char));
    if (!args_without_value)
        return;
    i = -1;
    while (++i < j)
        args_without_value[i] = args[i];
    args_without_value[i] = '\0';
	if (add_var(args_without_value, args, data) == 0)
    	free(args_without_value);
}
