/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:01:08 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/13 22:08:45 by epakdama         ###   ########.fr       */
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

int	ft_cd(char **args)
{
	if (arg_count(args) != 2)
		ft_exit_builtin("minishell: cd: too many arguments");
	if (chdir(args[1]))
		ft_exit_builtin("minishell: cd: a: No such file or directory");
	return (0);
}
