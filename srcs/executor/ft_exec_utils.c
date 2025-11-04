/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/04 10:28:52 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int		last_status;

	last_status = 0;
	while (count > 0)
	{
		pid = wait(&status);
		if (pid == -1)
		{
			perror("wait");
			break ;
		}
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != SIGPIPE)
				last_status = 128 + WTERMSIG(status);
		}
		count--;
	}
	g_exit_status = last_status;
}
