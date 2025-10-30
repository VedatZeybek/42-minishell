/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 00:00:00 by username          #+#    #+#             */
/*   Updated: 2025/10/31 01:01:58 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_executor.h"

static void	restore_fds(int saved_in, int saved_out)
{
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

static int	handle_builtin_redir(t_command *cmd, int saved_in, int saved_out)
{
	int	value;

	value = ft_handle_redirections(cmd);
	if (value != 0)
	{
		g_exit_status = value;
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		if (value == 1 && cmd->next)
			exit(0);
		return (1);
	}
	return (0);
}

static void	ft_execute_builtin(t_command *cmd, t_vars *vars, char **str)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (handle_builtin_redir(cmd, saved_in, saved_out))
		return ;
	if (ft_strncmp(cmd->argv[0].value, "exit", 4) == 0)
		ft_exit(str);
	g_exit_status = ft_run_builtin(cmd, vars);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
}

static void	handle_redir_only(t_command *cmd)
{
	int	saved_in;
	int	saved_out;
	int	ret;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	ret = ft_handle_redirections(cmd);
	if (ret != 0)
	{
		g_exit_status = ret;
		restore_fds(saved_in, saved_out);
		return ;
	}
	restore_fds(saved_in, saved_out);
}

void	ft_exec_single(t_command *cmd, t_vars *vars)
{
	char	**str;

	if ((!cmd->argv || !cmd->argv[0].value) && cmd->redirections)
	{
		handle_redir_only(cmd);
		return ;
	}
	if (!ft_is_builtin(cmd->argv[0].value))
	{
		ft_exec_pipe(cmd, vars);
		return ;
	}
	str = copy_argv_to_string_array(cmd, argv_length(cmd));
	ft_execute_builtin(cmd, vars, str);
	free_splitted(str);
}
