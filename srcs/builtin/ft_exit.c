/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:55:47 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 19:56:14 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(const char *str);

int	ft_exit_child(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
	{
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0)
		{
			perror("exit: numeric argument required\n");
			exit_code = 255;
		}
	}
	return (exit_code);
}

int	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			printf("exit\n");
			perror("minishell: exit: numeric argument required\n");
			free_splitted(args);
			exit(255);
		}
		exit_code = ft_atoi(args[1]);
		if (args[2])
		{
			perror("minishell: exit: too many arguments\n");
			g_exit_status = 1;
			free_splitted(args);
			return (1);
		}
	}
	free_splitted(args);
	printf("exit\n");
	exit((unsigned char)exit_code);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}
