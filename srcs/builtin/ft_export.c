/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:56:36 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 23:30:16 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static void	ft_set_env(t_vars *vars, char *key, char *value);
static int	ft_error_msg(char *arg);
static int	ft_is_valid_key(char *key);
static int	ft_update_env(t_vars *vars, char *key, char *value);

int	ft_export(t_vars *vars, char **args)
{
	char	*eq;
	char	*key;

	if (!vars || !args || !args[1])
		return (1);
	eq = ft_strchr(args[1], '=');
	if (eq)
		key = ft_substr(args[1], 0, eq - args[1]);
	else
		key = ft_strdup(args[1]);
	if (!key)
		return (1);
	if (ft_is_valid_key(key))
	{
		free(key);
		return (ft_error_msg(args[1]));
	}
	if (!eq)
	{
		free(key);
		return (0);
	}
	ft_set_env(vars, key, eq + 1);
	free(key);
	return (0);
}

static int	ft_error_msg(char *arg)
{
	write(2, "minishell: export: `", 21);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

static int	ft_is_valid_key(char *key)
{
	int	i;

	if (!key || !*key)
		return (1);
	if (ft_isdigit(key[0]))
		return (1);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_update_env(t_vars *vars, char *key, char *value)
{
	size_t	klen;
	char	*tmp;
	int		i;

	klen = ft_strlen(key);
	i = 0;
	while (vars->envp && vars->envp[i])
	{
		if (ft_strncmp(vars->envp[i], key, klen) == 0
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
	if (ft_update_env(vars, key, value))
		return ;
	new_env = ft_strjoin3(key, "=", value);
	if (!new_env)
		return ;
	vars->envp = ft_realloc_add(vars->envp, new_env);
}
