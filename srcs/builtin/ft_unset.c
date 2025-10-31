/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:04:03 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 17:08:22 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	if (!vars || !vars->envp || !key)
		return ;
	i = 0;
	j = 0;
	len = ft_strlen(key);
	new_env = malloc(sizeof(char *) * (ft_env_len(vars->envp) + 1));
	if (!new_env)
		return ;
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
