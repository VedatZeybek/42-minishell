/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:55:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 16:36:55 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	argv_length(t_command *cmd)
{
	size_t	len;

	len = 0;
	if (!cmd || !cmd->argv)
		return (0);
	while (cmd->argv[len].value != NULL)
		len++;
	return (len);
}

void	free_string_array(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_check_builtin(const char *c, const char *b)
{
	int	tmp;

	if (!c || !b)
		return (0);
	tmp = ft_strncmp(c, b, ft_strlen(b) + 1);
	if (tmp == 0)
		return (1);
	return (0);
}

const char *ft_get_env_elem(char **envp, char *elem_name)
{
	int     i;
	size_t  name_len;

	if (!envp || !elem_name)
		return (NULL);
	name_len = ft_strlen(elem_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], elem_name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}
