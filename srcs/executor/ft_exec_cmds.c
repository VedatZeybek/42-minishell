/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/25 14:29:38 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static void	ft_execute_builtin(t_command *cmd, t_vars *vars, char **str)
{
	int	saved_in;
	int	saved_out;
	int	value;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	value = ft_handle_redirections(cmd);
	if (value != 0)
	{
		g_exit_status = value;
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		if (value == 1 && cmd->next)
			exit(0);
		return ;
	}
	if (ft_strncmp(cmd->argv[0].value, "exit", 4) == 0)
		ft_exit(str);
	g_exit_status = ft_run_builtin(cmd, vars);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
}

void	ft_exec_single(t_command *cmd, t_vars *vars)
{
	char	**str;

	if (!ft_is_builtin(cmd->argv[0].value))
		ft_exec_pipe(cmd, vars);
	else
	{
		str = copy_argv_to_string_array(cmd, argv_length(cmd));
		ft_execute_builtin(cmd, vars, str);
		free_splitted(str);
	}
}
