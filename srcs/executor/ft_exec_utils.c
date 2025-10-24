/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 12:36:11 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

char	*ft_check_path(t_vars *vars, char *cmd)
{
	char	*temp;
	int		i;

	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = -1;
	while (vars->path && vars->path[++i])
	{
		temp = ft_strjoin_free(ft_strjoin(vars->path[i], "/"), cmd);
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
	}
	return (NULL);
}

int	ft_count_cmds(t_command *cmd_list)
{
	t_command	*tmp;
	int			i;

	i = 0;
	tmp = cmd_list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (i > 0)
		return (i);
	return (0);
}

void	wait_all_children(int count)
{
	pid_t	pid;
	int		status;

	while (count > 0)
	{
		pid = wait(&status);
		if (pid == -1)
			perror("wait");
		else if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != SIGPIPE)
				g_exit_status = 128 + WTERMSIG(status);
		}
		count--;
	}
}
