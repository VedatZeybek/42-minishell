/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:56:36 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 20:11:54 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*res;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	res = malloc(len1 + len2 + len3 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	ft_memcpy(res + len1 + len2, s3, len3);
	res[len1 + len2 + len3] = '\0';
	return (res);
}

char	**ft_realloc_add(char **arr, char *new_str)
{
	int		i;
	char	**new_arr;
	int		j;

	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	j = -1;
	while (j++ < i)
		new_arr[j] = arr[j];
	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}

int	ft_set_env_helper(t_vars *vars, char *key, char *value)
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

void	ft_set_env(t_vars *vars, char *key, char *value)
{
	char	*new_env;

	if (!vars || !key || !value)
		return ;
	ft_set_env_helper(vars, key, value);
	new_env = ft_strjoin3(key, "=", value);
	if (!new_env)
		return ;
	vars->envp = ft_realloc_add(vars->envp, new_env);
}

int	ft_export(t_vars *vars, char **args)
{
	char	*eq;
	int		i;

	if (!vars || !args)
		return (1);
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
