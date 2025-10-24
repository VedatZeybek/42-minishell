/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:56:36 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 18:22:09 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static void	ft_set_env(t_vars *vars, char *key, char *value);

int	ft_export(t_vars *vars, char **args)
{
	char	*eq;
	int		i;

	if (!vars || !args)
		return (1);
	if (!ft_is_valid_input(args[1]))
	{
		write(2, "minishell: export: `", 21);
		write(2, args[1], ft_strlen(args[1]));
		write(2, "': not a valid identifier\n", 27);
		return (1);
	}
	eq = ft_strchr(args[1], '=');
	i = 0;
	while (args[1][i])
	{
		if (!ft_isalnum(args[1][i]) && args[1][i] != '=')
			return (1);
		if (args[1][i] == '=')
			break ;
		i++;
	}
	if (ft_strlen(args[1]) == 1 || ft_isdigit(args[1][0]))
		return (1);
	if (!ft_strchr(args[1], '='))
		return (0);
	if (eq)
	{
		*eq = '\0';
		ft_set_env(vars, args[1], eq + 1);
	}
	return (0);
}

static int	ft_update_env(t_vars *vars, char *key, char *value)
{
	size_t	klen;
	size_t	elen;
	char	*tmp;
	int		i;

	klen = ft_strlen(key);
	i = 0;
	while (vars->envp && vars->envp[i])
	{
		elen = ft_strlen(vars->envp[i]);
		if (elen > klen && ft_strncmp(vars->envp[i], key, klen) == 0
			&& vars->envp[i][klen] == '=')
		{
			tmp = ft_strjoin3(key, "=", value);
			if (!tmp)
				return (1);
			free(vars->envp[i]);
			vars->envp[i] = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

static void	ft_set_env(t_vars *vars, char *key, char *value)
{
	char	*new_env;

	if (!vars || !key || !value)
		return ;
	ft_update_env(vars, key, value);
	new_env = ft_strjoin3(key, "=", value);
	if (!new_env)
		return ;
	vars->envp = ft_realloc_add(vars->envp, new_env);
}
