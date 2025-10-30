/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:31:19 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 00:07:34 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"
# include "stdio.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_WHITESPACE,
	TOKEN_INVALID
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

t_token				*tokenize(char *input);
t_token				*create_token(char *value, t_token_type type);
void				token_redirect(char *input, t_token **token, int *i);
void				add_token(t_token **head, t_token *new_token);
int					is_whitespace(char c);
void				free_tokens(t_token *token);
char				*ft_strjoin_free(char *s1, char *s2);
int					handle_word(char *input, t_token **token, int *i);
int					syntax_check(t_token *tok);
#endif