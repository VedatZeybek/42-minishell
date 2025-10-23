/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:37:26 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 12:10:51 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

int ft_run_commands(t_command *cmd_list, t_vars *vars)
{
	t_command	*tmp;
	int			n;
	
	tmp = cmd_list;
	if (!tmp || !vars)
		return 1;
	n = ft_count_cmds(cmd_list);
	if (n == 1)
		ft_exec_single(cmd_list, vars);
	else
		ft_exec_pipe(cmd_list, vars);
	return (g_exit_status);
}

