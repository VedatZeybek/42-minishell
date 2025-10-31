/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:21:43 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 12:17:38 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	token_redirect_in(char *input, t_token **token, int *i);
static void	token_redirect_out(char *input, t_token **token, int *i);

void	token_redirect(char *input, t_token **token, int *i)
{
	if (input[*i] == '>')
		token_redirect_out(input, token, i);
	else if (input[*i] == '<')
		token_redirect_in(input, token, i);
}

static void	token_redirect_in(char *input, t_token **token, int *i)
{
	if (input[*i + 1] == '<')
	{
		add_token(token, create_token("<<", TOKEN_HEREDOC));
		*i += 2;
	}
	else
	{
		add_token(token, create_token("<", TOKEN_REDIRECT_IN));
		(*i)++;
	}
}

static void	token_redirect_out(char *input, t_token **token, int *i)
{
	if (input[*i + 1] == '>')
	{
		add_token(token, create_token(">>", TOKEN_APPEND));
		*i += 2;
	}
	else
	{
		add_token(token, create_token(">", TOKEN_REDIRECT_OUT));
		(*i)++;
	}
}
