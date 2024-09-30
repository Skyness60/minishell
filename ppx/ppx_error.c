/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperron <sperron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:57:33 by sperron           #+#    #+#             */
/*   Updated: 2024/09/26 11:10:18 by sperron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ppx.h>

int	ppx_error(t_error_code code, char **av, int ac, char *cmd)
{
	if (code == ERR_FILE_NOT_FOUND)
		return (ft_dprintf(2, "bash: %s: No such file or directory\n",
				av[0]), 1);
	else if (code == ERR_ARGS)
		return (ft_dprintf(2,
				"bash: syntax error near unexpected token `%s'\n",
				av[ac - 1]), 2);
	else if (code == ERR_PERMISSION_DENIED)
		return (ft_dprintf(2, "bash: %s: Permission denied\n", cmd), 1);
	else if (code == ERR_CMD_NOT_FOUND)
		return (ft_dprintf(2, "bash: %s: command not found\n", cmd), 127);
	else if (code == ERR_PIPE_FAILURE)
		return (ft_dprintf(2, "bash: pipe failure\n"), 1);
	else if (code == ERR_FORK_FAILURE)
		return (ft_dprintf(2, "bash: fork failure\n"), 1);
	else if (code == ERR_HEREDOC)
		return (ft_dprintf(2, "bash: fork failure\n"), 1);
	else
		return (ft_dprintf(2, "bash: unknown error\n"), 1);
}
