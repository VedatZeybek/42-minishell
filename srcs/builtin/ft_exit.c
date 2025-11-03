/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:55:47 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/03 14:46:24 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_number(const char *str, long long *result);
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

int	ft_exit(char **args, t_vars *vars)
{
	int	exit_code;
	int	result;

	exit_code = 0;
	result = handle_exit_args(args, &exit_code, 0);
	if (result != 0)
		return (result);
	ft_putstr_fd("exit\n", 1);
	if (vars)
		ft_free_vars(vars);
	if (args[1] && is_all_number(args[1]) && !args[2])
		exit(ft_atoi(args[1]));
	exit(exit_code);
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
			ft_putendl_fd("minishell: exit: numeric argument required",
				STDERR_FILENO);
		*exit_code = 2;
		return (0);
	}
	if (args[2])
	{
		if (!is_child)
			ft_putendl_fd("minishell: exit: too many arguments",
				STDERR_FILENO);
		return (-1);
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
