/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:56:36 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 21:12:10 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_set_env(t_vars *vars, char *key, char *value);
static int	ft_error_msg(char *arg);
static int	ft_is_valid_key(char *key);
static int	ft_update_env(t_vars *vars, char *key, char *value);

int	ft_export(t_vars *vars, char **args)
{
	int		i;
	char	*eq;
	char	*key;

	if (!vars || !args || !args[1])
		return (1);
	i = 1;
	while (args[i])
	{
		eq = ft_strchr(args[i], '=');
		if (eq)
			key = ft_substr(args[i], 0, eq - args[i]);
		else
			key = ft_strdup(args[i]);
		if (!key)
			return (1);
		if (ft_is_valid_key(key))
			return (free(key), ft_error_msg(args[i]));
		if (!eq)
			return (free(key), 0);
		ft_set_env(vars, key, eq + 1);
		free(key);
		i++;
	}
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
