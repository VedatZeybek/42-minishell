/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:55:47 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 23:02:30 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

static int	is_valid_number(const char *str, long long *result);
static void	print_error(const char *msg);
static int	handle_exit_args(char **args, int *exit_code, int is_child);

int	ft_exit_child(char **args)
{
	int	exit_code;
	int	result;

	exit_code = 0;
	result = handle_exit_args(args, &exit_code, 1);
	if (result == -1)
		return (2);
	else if (result == 1)
		return (1);
	return ((unsigned char)exit_code);
}

int	ft_exit(char **args)
{
	int	exit_code;
	int	result;

	exit_code = 0;
	result = handle_exit_args(args, &exit_code, 0);
	printf("exit\n");
	free_splitted(args);
	if (result == -1)
		exit(2);
	else if (result == 1)
		exit(1);
	exit((unsigned char)exit_code);
}

static int	handle_exit_args(char **args, int *exit_code, int is_child)
{
	long long	num;

	*exit_code = 0;
	if (!args[1])
		return (0);
	if (!is_valid_number(args[1], &num))
	{
		if (!is_child)
			print_error("minishell: exit: numeric argument required");
		return (-1);
	}
	if (args[2])
	{
		if (!is_child)
			print_error("minishell: exit: too many arguments");
		return (1);
	}
	*exit_code = (int)num;
	return (0);
}

static int	is_valid_number(const char *str, long long *result)
{
	long long	num;
	int			sign;
	int			i;

	if (!str || !*str)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		if (num > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		num = num * 10 + (str[i++] - '0');
	}
	return (*result = num * sign, 1);
}

static void	print_error(const char *msg)
{
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
