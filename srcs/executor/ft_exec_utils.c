/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 17:54:01 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static char	*ft_strjoin_custom(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] && s2[j] != ' ')
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}

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
		temp = ft_strjoin_custom(ft_strjoin(vars->path[i], "/"), cmd);
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
