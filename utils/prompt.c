/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlebard <jlebard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:54:47 by jlebard           #+#    #+#             */
/*   Updated: 2024/08/07 17:04:47 by jlebard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var_env(char **env, char *var)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0 &&
			env[ft_strlen(var) == '='])
		return (env[i] + ft_strlen(var) + 1);
	}
	return (NULL);
}

char	*get_home(char **env)
{
	
}

char	*create_prompt(char **env)
{
	
}