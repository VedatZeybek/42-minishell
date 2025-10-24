/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:04:03 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 14:55:26 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static void	ft_remove_env(t_vars *vars, char *key);

int	ft_unset(t_vars *vars, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_remove_env(vars, args[i]);
		i++;
	}
	return (0);
}

static void	ft_remove_env(t_vars *vars, char *key)
{
	int		i;
	int		j;
	size_t	len;
	char	**new_env;

	i = 0;
	j = 0;
	len = ft_strlen(key);
	new_env = malloc(sizeof(char *) * (ft_env_len(vars->envp)));
	while (vars->envp[i])
	{
		if (!(ft_strncmp(vars->envp[i], key, len) == 0
				&& vars->envp[i][len] == '='))
			new_env[j++] = vars->envp[i];
		else
			free(vars->envp[i]);
		i++;
	}
	new_env[j] = NULL;
	free(vars->envp);
	vars->envp = new_env;
}
