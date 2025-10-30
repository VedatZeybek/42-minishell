/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:22:21 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 01:29:45 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static void	setup_child_pipes(int prev_fd[2], int curr_fd[2], t_command *cmd);
static int	handle_redirections(t_command *cmd);

void	exec_child_process(t_command *cmd, t_command *cmd_list_head,
						t_vars *vars, t_pipes *pipes)
{
	int	value;

	setup_child_pipes(pipes->prev, pipes->curr, cmd);
	handle_redirections(cmd);
	if (ft_is_builtin(cmd->argv[0].value))
	{
		value = ft_run_builtin(cmd, vars);
		free_command_list(cmd_list_head);
		ft_free_vars(vars);
		exit(value);
	}
	else
	{
		value = ft_run_external_cmd(cmd, vars);
		if (value == 0 && cmd->next)
			g_exit_status = 0;
		else
		{
			free_command_list(cmd_list_head);
			ft_free_vars(vars);
			exit(value);
		}
	}
}

static void	setup_child_pipes(int prev_fd[2], int curr_fd[2], t_command *cmd)
{
	if (prev_fd[0] != -1)
	{
		dup2(prev_fd[0], STDIN_FILENO);
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
	if (cmd->next)
	{
		dup2(curr_fd[1], STDOUT_FILENO);
		close(curr_fd[0]);
		close(curr_fd[1]);
	}
}

static int	handle_redirections(t_command *cmd)
{
	int	backup_in;
	int	backup_out;
	int	value;

	backup_in = dup(STDIN_FILENO);
	backup_out = dup(STDOUT_FILENO);
	value = ft_handle_redirections(cmd);
	if (value != 0)
	{
		dup2(backup_in, STDIN_FILENO);
		dup2(backup_out, STDOUT_FILENO);
		close(backup_in);
		close(backup_out);
		if (value == 1 && cmd->next)
			exit(0);
		exit(value);
	}
	close(backup_in);
	close(backup_out);
	return (value);
}
