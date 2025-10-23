/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:01:08 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 19:52:02 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_to(const char *path)
{
	if (!path)
	{
		perror("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	ft_cd(char **args)
{
	int			n;
	const char	*home;

	n = ft_arg_count(args);
	if (n == 1)
	{
		home = getenv("HOME");
		return (cd_to(home));
	}
	if (n > 2)
		return (perror("minishell: cd: too many arguments\n"), 1);
	return (cd_to(args[1]));
}
