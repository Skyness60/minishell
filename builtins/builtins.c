/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:18:14 by sperron           #+#    #+#             */
/*   Updated: 2024/09/13 16:16:08 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//int	is_builtin(t_data *data, int fd)
//{
//	if (!ft_strcmp(data->input, "pwd"))
//		return (handle_pwd(data->ac - 1));
//	else if (!ft_strcmp(data->input, "echo"))
//		return (handle_echo(data->av + 1, data->ac - 1, fd));
//	else if (!ft_strcmp(data->input, "cd"))
//		return (handle_cd(data->av + 1, data->ac - 1));
//	else if (!ft_strcmp(data->input, "env"))
//		return (handle_env(data, fd));
//	else if (!ft_strcmp(data->input, "unset"))
//		return (handle_unset(data, data->av));
//	else if (!ft_strcmp(data->input, "export"))
//		return (handle_export(data, data->av, data->ac, fd));
//	else
//		return (127);
//}
