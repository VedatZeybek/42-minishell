/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 15:07:04 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

void	ft_exec_single(t_command *cmd, t_vars *vars)
{
	pid_t	pid;
	int		s;

	if (ft_handle_redirections(cmd) != 0)
		return ;
	if (ft_is_builtin(cmd->argv[0]))
	{
		vars->status = ft_run_builtin(cmd, vars->envp);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		ft_run_external_cmd(cmd, vars);
		exit(1);
	}
	else if (pid > 0)
		waitpid(pid, &s, 0);
	vars->status = s;
}

static void	ft_child1(t_command *cmd, t_vars *vars, int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (ft_is_builtin(cmd->argv[0]))
		exit(ft_run_builtin(cmd, vars->envp));
	else
		ft_run_external_cmd(cmd, vars);
	exit(1);
}

static void	ft_child2(t_command *cmd, t_vars *vars, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (ft_is_builtin(cmd->argv[0]))
		exit(ft_run_builtin(cmd, vars->envp));
	else
		ft_run_external_cmd(cmd, vars);
	exit(1);
}

static void	ft_close_and_wait(int *fd, pid_t pid1, pid_t pid2)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	ft_exec_pipe(t_command *cmd_list, t_vars *vars)
{
	t_command	*cmd;
	int			fd[2];
	pid_t		pid1;
	pid_t		pid2;

	if (pipe(fd) == -1)
		return ;
	cmd = cmd_list;
	pid1 = fork();
	if (pid1 == -1)
		return ;
	if (pid1 == 0)
		ft_child1(cmd, vars, fd);
	cmd = cmd->next;
	if (cmd)
	{
		pid2 = fork();
		if (pid2 == -1)
			return ;
		if (pid2 == 0)
			ft_child2(cmd, vars, fd);
	}
	ft_close_and_wait(fd, pid1, pid2);
}
