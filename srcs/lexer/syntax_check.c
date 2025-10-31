/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:14:26 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 21:14:26 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redir_sequence(t_token **cur)
{
	while (*cur && is_redir((*cur)->type))
	{
		if (!(*cur)->next || (*cur)->next->type != TOKEN_WORD)
		{
			if (!(*cur)->next)
				return (syntax_error("newline"));
			else
				return (syntax_error(token_repr((*cur)->next->type)));
		}
		*cur = (*cur)->next->next;
	}
	return (0);
}

static int	handle_expecting_cmd(t_token **cur, int *expecting_cmd)
{
	if (check_redir_sequence(cur))
		return (1);
	if (*cur && (*cur)->type == TOKEN_WORD)
	{
		*expecting_cmd = 0;
		*cur = (*cur)->next;
		return (0);
	}
	if (*cur && (*cur)->type == TOKEN_PIPE)
		return (syntax_error("|"));
	return (0);
}

static int	handle_after_cmd_redir(t_token **cur)
{
	if (!(*cur)->next)
		return (syntax_error("newline"));
	if ((*cur)->next->type != TOKEN_WORD)
		return (syntax_error(token_repr((*cur)->next->type)));
	*cur = (*cur)->next->next;
	return (0);
}

static int	handle_after_cmd(t_token **cur, int *expecting_cmd)
{
	if (is_redir((*cur)->type))
		return (handle_after_cmd_redir(cur));
	if ((*cur)->type == TOKEN_WORD)
	{
		*cur = (*cur)->next;
		return (0);
	}
	if ((*cur)->type == TOKEN_PIPE)
	{
		*expecting_cmd = 1;
		*cur = (*cur)->next;
		if (!*cur)
			return (syntax_error("newline"));
		if ((*cur)->type == TOKEN_PIPE)
			return (syntax_error("|"));
		return (0);
	}
	return (syntax_error("newline"));
}

int	syntax_check(t_token *tok)
{
	t_token	*cur;
	int		expecting_cmd;

	cur = tok;
	expecting_cmd = 1;
	if (!cur)
		return (0);
	if (cur->type == TOKEN_PIPE)
		return (syntax_error("|"));
	while (cur)
	{
		if (expecting_cmd)
		{
			if (handle_expecting_cmd(&cur, &expecting_cmd))
				return (1);
		}
		else
		{
			if (handle_after_cmd(&cur, &expecting_cmd))
				return (1);
		}
	}
	return (0);
}
