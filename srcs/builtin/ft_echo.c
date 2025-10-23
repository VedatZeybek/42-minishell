/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:04:09 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 20:08:18 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo_helper(int *i, int is_new_line)
{
	if (!is_new_line)
		*i = 2;
	else
		*i = 1;
}

void	ft_echo_helper2(int *i, int *is_new_line, char **args)
{
	while (args[1][*i] == 'n' && args[1][*i])
		(*i)++;
	if (!args[1][*i])
		*is_new_line = 0;
}

int	ft_echo(char **args)
{
	int	i;
	int	is_new_line;

	is_new_line = 1;
	if (ft_arg_count(args) == 0)
	{
		return (printf("\n"), 0);
	}
	i = 1;
	if (args[i] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		ft_echo_helper2(&i, &is_new_line, args);
	}
	ft_echo_helper(&i, is_new_line);
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
