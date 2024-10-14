/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:15:44 by sperron           #+#    #+#             */
/*   Updated: 2024/10/14 15:29:35 by sperron          ###   ########.fr       */
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

int export_error(char *argv)
{
    write(2, "bash: export: '", 16);
    write(2, argv, ft_strlen(argv));
    write(2, "' :not a valid identifier\n", 27);
    return (1);
}


static void add_env_var(t_data *data, char *var)
{
    size_t 	j;
	char	**new_env;

	j = 0;
    while (data->env[j])
		j++;
    new_env = ft_realloc_char(data->env, j * sizeof(char *), (j + 2) * sizeof(char *));
    if (!new_env)
	{
        perror("Failed to expand environment");
        free(var);
        return;
    }
    new_env[j] = var;
    new_env[j + 1] = NULL;
    data->env = new_env;
}

int handle_export(t_data *data, char **args, int ac, int fd)
{
    int 	out;
	int		i;
	char	*var;

    if (ac == 0)
		return (sort_export(data, fd));
	out = 0;
	i = 0;
	while (args[i])
	{
        if (!is_valid_identifier(args[i]))
            out = export_error(args[i]);
        else if (ft_strchr(args[i], '='))
		{
            var = ft_strdup(args[i]);
            if (!var)
				return (perror_exit("Error duplicating string", 1), 1);
            if (!update_env(data, var))
                add_env_var(data, var);
        }
		i++;
	}
    return (out);
}