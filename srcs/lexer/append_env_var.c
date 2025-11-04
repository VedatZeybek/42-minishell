/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:58:53 by vzeybek	       #+#    #+#             */
/*   Updated: 2025/11/04 10:32:40 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_exit_status(char **buffer, int *i)
{
	char	*value;

	value = ft_itoa(g_exit_status);
	*buffer = ft_strjoin_free(*buffer, value);
	free(value);
	(*i)++;
}

static char	*extract_var_name(char *input, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (NULL);
	var_name = ft_substr(input, start, *i - start);
	return (var_name);
}

void	append_env_var(char **buffer, char *input, int *i, t_vars *vars)
{
	char	*var_name;
	char	*value;

	if (input[++*i] == '?')
	{
		append_exit_status(buffer, i);
		return ;
	}
	var_name = extract_var_name(input, i);
	if (!var_name)
	{
		*buffer = ft_strjoin_free(*buffer, "$");
		return ;
	}
	value = (char *)ft_get_env_elem(vars->envp, var_name);
	if (value && value[0] != '\0')
		*buffer = ft_strjoin_free(*buffer, value);
	free(var_name);
}
