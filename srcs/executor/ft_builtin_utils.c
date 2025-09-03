/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:55:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 15:07:04 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

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

int	ft_call_builtin(t_command *cmd, char **envp)
{
	if (ft_check_builtin(cmd->argv[0], "echo"))
		return (ft_echo(cmd->argv));
	else if (ft_check_builtin(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv));
	else if (ft_check_builtin(cmd->argv[0], "pwd"))
		return (ft_pwd(cmd->argv));
	else if (ft_check_builtin(cmd->argv[0], "env"))
		return (ft_env(cmd->argv, envp));
	return (0);
}
