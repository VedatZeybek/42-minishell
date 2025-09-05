/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:37:26 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 15:04:07 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

int	ft_run_commands(t_command *cmd_list, char **envp)
{
	t_vars	vars;
	int		n;

	if (!cmd_list || !envp)
		return (1);
	n = ft_count_cmds(cmd_list);
	ft_init_vars(&vars, envp);
	if (n == 1)
		ft_exec_single(cmd_list, &vars);
	else
	{
		ft_exec_pipe(cmd_list, &vars);
	}
	return (vars.status);
}
