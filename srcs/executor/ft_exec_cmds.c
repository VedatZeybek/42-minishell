/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 16:38:04 by vzeybek          ###   ########.fr       */
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
		if (cmd->next && pipe(curr_fd) == -1)
			return ;
			
		pid = fork();
		if (pid == -1)
			return ;

		if (pid == 0)
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
			int backup_in = dup(STDIN_FILENO);
			int backup_out = dup(STDOUT_FILENO);
			int value = ft_handle_redirections(cmd);
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
			if (ft_is_builtin(cmd->argv[0].value))
			{
				exit(ft_run_builtin(cmd, vars));
			}
			else
			{
				value = ft_run_external_cmd(cmd, vars);
				if (value == 0 && cmd->next)
				{
					g_exit_status = 0;
				}
				else
					exit(value);
			}
		}
		if (prev_fd[0] != -1)
		{
			close(prev_fd[0]);
			close(prev_fd[1]);
		}
		if (cmd->next)
		{
			prev_fd[0] = curr_fd[0];
			prev_fd[1] = curr_fd[1];
		}
		cmd = cmd->next;
		i++;
	}
	int status;

	while (i-- > 0)
	{
		pid = wait(&status);
		if (pid == -1)
			perror("wait");
		else
		{
			if (WIFEXITED(status))
			{
				int exit_code = WEXITSTATUS(status);
				g_exit_status = exit_code;
			}
			else if (WIFSIGNALED(status))
			{
				int sig = WTERMSIG(status);
				if (sig == SIGPIPE)
					continue ; // ignore
				g_exit_status = 128 + sig;
			}
		}
	}
}
