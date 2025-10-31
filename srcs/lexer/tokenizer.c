/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:21:50 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 12:17:44 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_operators(char *input, t_token **token, int *i)
{
	if (input[*i] == '|')
	{
		add_token(token, create_token("|", TOKEN_PIPE));
		(*i)++;
		return (1);
	}
	if (input[*i] == '>' || input[*i] == '<')
	{
		token_redirect(input, token, i);
		return (1);
	}
	return (0);
}

static int	process_token(char *input, t_token **token, int *i)
{
	if (handle_operators(input, token, i))
		return (1);
	if (handle_word(input, token, i))
		return (1);
	if (input[*i] && !is_whitespace(input[*i]))
	{
		write(2, "minishell: unexpected character '", 34);
		write(2, &input[*i], 1);
		write(2, "'\n", 2);
		free_tokens(*token);
		return (0);
	}
	return (1);
}

t_token	*tokenize(char *input)
{
	t_token	*token;
	int		i;

	token = NULL;
	i = 0;
	if (!input || !*input)
		return (NULL);
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		if (!process_token(input, &token, &i))
			return (NULL);
	}
	return (token);
}
