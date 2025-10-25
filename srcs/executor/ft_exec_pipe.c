/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:22:26 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/25 14:22:26 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static int	create_pipe_and_fork(t_command *cmd, int curr_fd[2]);
static int	create_pipe_and_fork(t_command *cmd, int curr_fd[2]);
static void	close_prev_pipes(int prev_fd[2]);
static void	arrange_pipes(t_command *cmd, int prev_fd[2], int curr_fd[2]);

void	ft_exec_pipe(t_command *cmd_list, t_vars *vars)
{
	t_command	*cmd;
	int			prev_fd[2];
	int			curr_fd[2];
	pid_t		pid;
	int			i;

	cmd = cmd_list;
	prev_fd[0] = -1;
	prev_fd[1] = -1;
	i = 0;
	while (cmd)
	{
		pid = create_pipe_and_fork(cmd, curr_fd);
		if (pid == -1)
			return ;
		if (pid == 0)
			exec_child_process(cmd, vars, prev_fd, curr_fd);
		arrange_pipes(cmd, prev_fd, curr_fd);
		cmd = cmd->next;
		i++;
	}
	wait_all_children(i);
}

static int	create_pipe_and_fork(t_command *cmd, int curr_fd[2])
{
	if (cmd->next && pipe(curr_fd) == -1)
		return (-1);
	return (fork());
}

static void	close_prev_pipes(int prev_fd[2])
{
	if (prev_fd[0] != -1)
	{
		close(prev_fd[0]);
		close(prev_fd[1]);
	}
}

static void	arrange_pipes(t_command *cmd, int prev_fd[2], int curr_fd[2])
{
	close_prev_pipes(prev_fd);
	if (cmd->next)
	{
		prev_fd[0] = curr_fd[0];
		prev_fd[1] = curr_fd[1];
	}
}
