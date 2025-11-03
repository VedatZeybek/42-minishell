/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 23:02:56 by vedat-zeybe       #+#    #+#             */
/*   Updated: 2025/11/03 23:08:08 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_substr_to_buffer(char **buffer, char *input,
			int start, int end)
{
	char	*tmp;
	char	*newbuf;

	if (end <= start)
		return ;
	tmp = ft_substr(input, start, end - start);
	if (!tmp)
		return ;
	newbuf = ft_strjoin(*buffer, tmp);
	free(tmp);
	free(*buffer);
	*buffer = newbuf;
}

void	append_double_quote(char **buffer, char *input,
			int *i, t_vars *vars)
{
	int		start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			if (*i > start)
				append_substr_to_buffer(buffer, input, start, *i);
			append_env_var(buffer, input, i, vars);
			start = *i;
			continue ;
		}
		(*i)++;
	}
	if (*i > start)
		append_substr_to_buffer(buffer, input, start, *i);
	if (input[*i] == '"')
		(*i)++;
}
