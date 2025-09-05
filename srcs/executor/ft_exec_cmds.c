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

int	ft_is_builtin(char *cmd_name);

void	ft_exec_single(t_command *cmd, t_vars *vars)
{
	char	**str;

	str = copy_argv_to_string_array(cmd, argv_length(cmd));
	if (!ft_is_builtin(cmd->argv[0].value))
		ft_exec_pipe(cmd, vars);
	else
	{
		if (ft_handle_redirections(cmd) != 0)
			return ;
		if (ft_is_builtin(cmd->argv[0].value))
		{
			if (ft_strncmp(cmd->argv[0].value, "exit", 4) == 0)
				ft_exit(str);	
			vars->status = ft_run_builtin(cmd, vars);
			return ;
		}
	}
}

//new exec_pipe
void	ft_exec_pipe(t_command *cmd_list, t_vars *vars)
{
	t_command	*cmd;
	int			prev_fd[2]; // önceki pipe
	int			curr_fd[2]; // şimdiki pipe
	pid_t		pid;
	int			i;
	
	cmd = cmd_list;
	prev_fd[0] = -1;
	prev_fd[1] = -1;
	i = 0;
	while (cmd)
	{
		// Son komut değilse yeni pipe aç
		if (cmd->next && pipe(curr_fd) == -1)
			return ;
			
		pid = fork();
		if (pid == -1)
			return ;

		if (pid == 0) // child process
		{
			//signal(SIGINT, SIG_DFL);
    		//signal(SIGQUIT, SIG_DFL);
			// stdin ayarla
			if (prev_fd[0] != -1)
			{
				dup2(prev_fd[0], STDIN_FILENO);
				close(prev_fd[0]);
				close(prev_fd[1]);
			}
			// stdout ayarla
			if (cmd->next)
			{
				dup2(curr_fd[1], STDOUT_FILENO);
				close(curr_fd[0]);
				close(curr_fd[1]);
			}
			if (ft_is_builtin(cmd->argv[0].value))
				exit(ft_run_builtin(cmd, vars));
			else
			{
				if (!ft_handle_redirections(cmd))
					ft_run_external_cmd(cmd, vars);
				exit(127); // exec başarısızsa default
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
	// parent tüm çocukları beklesin
	int status;

	while (i-- > 0)
	{
		pid = wait(&status);
		if (pid == -1)
			perror("wait");
		else
		{
			if (WIFEXITED(status))  // normal exit
			{
				int exit_code = WEXITSTATUS(status);
				// burada exit_code, çocuğun return value’su
				g_exit_status = exit_code;
			}
			else if (WIFSIGNALED(status)) // sinyalle öldüyse
			{
				int sig = WTERMSIG(status);
				g_exit_status = 128 + sig; // bash uyumlu
			}
		}
	}
}

	//void	ft_exec_pipe(t_command *cmd_list, t_vars *vars)
//{
	//	t_command	*cmd;
	//	int			fd[2];
//	pid_t		pid1;
//	pid_t		pid2;

//	if (pipe(fd) == -1)
//		return ;
//	cmd = cmd_list;
//	pid1 = fork();
//	if (pid1 == -1)
//		return ;
//	if (pid1 == 0)
//		ft_child1(cmd, vars, fd);
//	cmd = cmd->next;
//	if (cmd)
//	{
	//		pid2 = fork();
//		if (pid2 == -1)
//			return ;
//		if (pid2 == 0)
//			ft_child2(cmd, vars, fd);
//	}
//	ft_close_and_wait(fd, pid1, pid2);
//}


//static void	ft_child1(t_command *cmd, t_vars *vars, int *fd)
//{
//	dup2(fd[1], STDOUT_FILENO);
//	close(fd[0]);
//	close(fd[1]);
//	if (ft_is_builtin(cmd->argv[0].value))
//		exit(ft_run_builtin(cmd, vars->envp));
//	else
//		ft_run_external_cmd(cmd, vars);
//	exit(1);
//}

//static void	ft_child2(t_command *cmd, t_vars *vars, int *fd)
//{
//	dup2(fd[0], STDIN_FILENO);
//	close(fd[0]);
//	close(fd[1]);
//	if (ft_is_builtin(cmd->argv[0].value))
//		exit(ft_run_builtin(cmd, vars->envp));
//	else
//		ft_run_external_cmd(cmd, vars);
//	exit(1);
//}

//static void	ft_close_and_wait(int *fd, pid_t pid1, pid_t pid2)
//{
//	close(fd[0]);
//	close(fd[1]);
//	waitpid(pid1, NULL, 0);
//	waitpid(pid2, NULL, 0);
//}