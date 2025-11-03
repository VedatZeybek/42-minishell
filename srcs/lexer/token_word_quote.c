/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:21:45 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/03 23:04:32 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_single_quote(char **buffer, char *input, int *i)
{
	int		start;
	char	*tmp;
	char	*newbuf;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (*i > start)
	{
		tmp = ft_substr(input, start, (*i) - start);
		if (tmp)
		{
			newbuf = ft_strjoin(*buffer, tmp);
			free(tmp);
			free(*buffer);
			*buffer = newbuf;
		}
	}
	if (input[*i] == '\'')
		(*i)++;
}

static void	process_word(char **buffer, char *input, int *i, t_vars *vars)
{
	char	temp[2];

	if (input[*i] == '\'')
		append_single_quote(buffer, input, i);
	else if (input[*i] == '"')
		append_double_quote(buffer, input, i, vars);
	else if (input[*i] == '$')
		append_env_var(buffer, input, i, vars);
	else
	{
		temp[0] = input[*i];
		temp[1] = '\0';
		*buffer = ft_strjoin_free(*buffer, temp);
		(*i)++;
	}
}

int	handle_word(char *input, t_token **token, int *i, t_vars *vars)
{
	char	*buffer;
	int		start_i;

	start_i = *i;
	buffer = ft_strdup("");
	while (input[*i] && !is_whitespace(input[*i])
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		process_word(&buffer, input, i, vars);
	}
	if (*i > start_i)
	{
		add_token(token, create_token(buffer, TOKEN_WORD));
		free(buffer);
		return (1);
	}
	free(buffer);
	if (*i > start_i)
		return (1);
	return (0);
}
