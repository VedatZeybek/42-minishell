/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:18:23 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/01 18:24:57 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_valid_checks(char *key, char *eq, char *args)
{
	if (!key)
		return (1);
	if (ft_is_valid_key(key))
		return (ft_error_msg(args));
	if (!eq)
		return (0);
	return (-1);
}

int	print_exports(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(vars->envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}
