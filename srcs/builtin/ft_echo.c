/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:04:09 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 11:12:32 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int	is_new_line;

	is_new_line = 1;
	if (arg_count(args) == 0)
	{
		return (printf("\n"), 0);
	}
	i = 1;
	if (args[i] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		while (args[1][i] == 'n' && args[1][i])
			i++;
		if (!args[1][i])
			is_new_line = 0;
	}
	i = 1;
	if (!is_new_line)
		i = 2;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (is_new_line)
		printf("\n");
	return (0);
}
