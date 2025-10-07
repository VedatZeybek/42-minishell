/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 18:00:36 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

int	ft_is_builtin(char *cmd_name);

void	ft_exec_single(t_command *cmd, t_vars *vars)
{
	char	**str;

	if (!ft_is_builtin(cmd->argv[0].value))
		ft_exec_pipe(cmd, vars);
	else
	{
		str = copy_argv_to_string_array(cmd, argv_length(cmd));
		int saved_in = dup(STDIN_FILENO);
		int saved_out = dup(STDOUT_FILENO);
		int value = ft_handle_redirections(cmd); 
		if (value != 0)
		{
			g_exit_status = (value);
			dup2(saved_in, STDIN_FILENO);
			dup2(saved_out, STDOUT_FILENO);
			if (value == 1 && cmd->next)
				exit(0);
			return ;
		}
		if (ft_is_builtin(cmd->argv[0].value))
		{
			if (ft_strncmp(cmd->argv[0].value, "exit", 4) == 0)
				ft_exit(str);
			g_exit_status = ft_run_builtin(cmd, vars);
			dup2(saved_in, STDIN_FILENO);
			dup2(saved_out, STDOUT_FILENO);
			return ;
		}
	}
}
