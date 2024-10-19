/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:47:57 by sperron           #+#    #+#             */
/*   Updated: 2024/10/17 17:15:47 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void handle_env_value(char **str, char *env_value, int i, t_data *data)
{
    char    *tmp;
    char    *new_str;
    int     j;

    (void)data;
    j = i + 1;
    while (ft_isalnum((*str)[j]) || (*str)[j] == '_')
        j++;
    tmp = ft_substr(*str, 0, i);
    new_str = ft_strjoin(tmp, env_value);
    free(tmp);
    tmp = ft_strjoin(new_str, *str + j);
    free(new_str);
    free(*str);
    *str = tmp;
}

static void handle_no_env_value(char **str, int i, int j, t_data *data)
{
    char *tmp;
    char *new_str;

    (void)data;
    tmp = ft_substr(*str, 0, i);
    new_str = ft_strjoin(tmp, *str + j);
    free(tmp);
    free(*str);
    *str = new_str;
    add_ptr(data->trash, *str);
}

static char *handle_exit_code(char *var_name, t_data *data)
{
    int     i;
    int     j;
    char    *result;
    char    *tmp;
    char    *exit_code_str;

    i = 0;
    j = 0;
    result = NULL;
    exit_code_str = NULL;
    while (var_name[i])
    {
        if (var_name[i] == '$' && var_name[i + 1] == '?')
        {
            exit_code_str = ft_itoa(data->cmd_exit_status);
            if (!exit_code_str)
                perror_exit("Error w/ malloc\n", 2, data);
            tmp = ft_substr(var_name, 0, i);
            result = ft_strjoin(tmp, exit_code_str);
            free(tmp);
            free(exit_code_str);
            tmp = ft_strjoin(result, var_name + i + 2);
            free(result);
            result = tmp;
        }
        i++;
    }
    if (!result)
        result = ft_strdup(var_name);
    return result;
}

static char *replace_var(const char *str, t_data *data)
{
    int     i;
    int     j;
    char    *var_name;
    char    *env_value;
    char    *new_str;
    char    *tmp;
    int     count;

    count = 0;
    i = 0;
    if (!str || !str[0])
        return (NULL);

    new_str = ft_strdup(str);  // Copie de la chaîne originale

    while (new_str[i] != '\0')
    {
        if (new_str[i] == '$' && new_str[i + 1] && (ft_isalnum(new_str[i + 1]) || new_str[i + 1] == '_'))
        {
            j = i + 1;
            while (ft_isalnum(new_str[j]) || new_str[j] == '_')
                j++;
            var_name = ft_substr(new_str, i + 1, j - i - 1);
            env_value = get_var_in_env(data->env, var_name, data);
            free(var_name);
            if (env_value)
                handle_env_value(&new_str, env_value, i, data);
            else
			{
                handle_no_env_value(&new_str, i, j, data);
				if (new_str[0] == '\0')
					break ;
			}
        }
        else if (new_str[i] == '$' && new_str[i + 1] == '?')
        {
            tmp = handle_exit_code(new_str, data);
            free(new_str);
            new_str = tmp;
        }
        i++;
    }
    return new_str;
}

void replace_vars_in_tokens(char **tokens, t_data *data)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        char *new_token = replace_var(tokens[i], data);
        free(tokens[i]);  // Libérer l'ancien token
        tokens[i] = new_token;

        if (tokens[i][0] == '\0')
        {
            tokens[i] = NULL;
        }
        i++;
    }
    //add_ptr_tab(data->trash, (void **)tokens, array_len(tokens), false);
}
