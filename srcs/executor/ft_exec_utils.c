/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 15:04:07 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static char	**ft_init_env(char **envp)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			res = ft_split(ft_strchr(envp[i], '=') + 1, ':');
			break ;
		}
		i++;
	}
	return (res);
}

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


char **ft_env_dup(char **envp)
{
    int len = ft_env_len(envp);
    char **dup = malloc(sizeof(char *) * (len + 1));
    if (!dup)
        return NULL;
    for (int i = 0; i < len; i++)
        dup[i] = ft_strdup(envp[i]);
    dup[len] = NULL;
    return dup;
}

void	ft_init_vars(t_vars *vars, char **envp)
{
	vars->envp = ft_env_dup(envp);
	vars->path = ft_init_env(envp);
	vars->status = 0;
}
