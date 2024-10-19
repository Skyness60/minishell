/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:47:57 by sperron           #+#    #+#             */
/*   Updated: 2024/10/19 14:55:34 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *delete_dollar(char *str, int size_d)
{
    int     i;
    int     j;
    char    *dest;
    
    i = -1;
    j = -1;
    while (str[++i] != '$')
        ;
    dest = malloc ((i + ft_strlen(str + i + size_d - 1) + 1) * sizeof(char));
    i = -1;
    while (str[++i] != '$')
        dest[++j] = str[i];
    while (str[++i + size_d - 1])
        dest[++j] = str[i + size_d - 1];
    dest[j + 1] = '\0';
    free(str);
    return (dest);
}

static char *replace_in_str(char *str, char *env_value, int size_d)
{
    int     i;
    char    *dest;
    int     j;
    int     k;
    
    i = -1;
    k = -1;
    if (!env_value)
        return (delete_dollar(str, size_d));
    while (str[++i] != '$')
        ;
    dest = malloc(i + ft_strlen(env_value) + \
    ft_strlen(str + i + size_d - 1) + 1);
    j = -1;
    while (str[++j] != '$')
        dest[++k] = str[j];
    j = -1;
    while (env_value[++j])
        dest[++k] = env_value[j];
    j = size_d + i;
    while (str[j])
        dest[++k] = str[j++];
    dest[k + 1] = '\0';
    return (free(str), dest);
}

static char *replace_var(char *str, t_data *data)
{
    int     i;
    int     j;
    char    *dollar_value;
    char    *env_value;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '$' && str[i + 1])
        {
            j = 0;  
            if (str[i + ++j] == '?')
                j = 1;
            else
                while (ft_isalpha(str[i + ++j]) || str[i + j] == '_')
                    ;
            dollar_value = ft_substr(str, i + 1, j - 1);
            env_value = get_var_in_env(data->env, dollar_value, data);
            str = replace_in_str(str, env_value, \
            (int)ft_strlen(dollar_value) + 1);
            free(dollar_value);
            i = -1;
        }
    }
    return (str);
}
static bool no_dollar(char *str)
{
    while (*str)
    {
        if (*str == '$')
            return (false);
        str++;
    }
    return (true);
}

void replace_vars_in_tokens(char **tokens, t_data *data)
{
    int i;

    i = -1;
    while (tokens[++i])
    {
        if (no_dollar(tokens[i]))
            continue ;
        tokens[i] = replace_var(tokens[i], data);
        if (tokens[i][0] == '\0')
            tokens[i] = tokens[i + 1];
    }
    add_ptr_tab(data->trash, (void **)tokens, \
		(int)array_len(tokens), true);
}
