/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/09/12 11:15:29 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_data *data, int fd)
{
	if (!ft_strcmp(data->input, "pwd"))
		return (pwd(data->ac - 1));
	else if (!ft_strcmp(data->input, "echo"))
		return (echo(data->av + 1, data->ac - 1, fd));
	else if (!ft_strcmp(data->input, "cd"))
		return (cd(data->av + 1, data->ac - 1));
	else if (!ft_strcmp(data->input, "env"))
		return (env(data, fd));
	else if (!ft_strcmp(data->input, "unset"))
		return (unset(data, data->av));
	else if (!ft_strcmp(data->input, "export"))
		return ();
	else
		return (127);
}
