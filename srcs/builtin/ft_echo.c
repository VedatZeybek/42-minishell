/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:04:09 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 11:49:15 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	is_new_line;

	is_new_line = 1;
	i = 1;
	if (args[i] && ft_strncmp(args[i], "-n", 3) == 0)
	{
		is_new_line = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (is_new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
