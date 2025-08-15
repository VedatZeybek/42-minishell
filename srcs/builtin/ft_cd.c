/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:01:08 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/13 22:54:36 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	cd_to(const char *path)
{
	if (!path)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_cd(char **args)
{
	int			n;
	const char	*home;

	n = arg_count(args);
	if (n == 1)
	{
		home = getenv("HOME");
		return (cd_to(home));
	}
	if (n > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (cd_to(args[1]));
}
