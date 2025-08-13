#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,			// Regular command or argument
	TOKEN_PIPE,			// |
	TOKEN_REDIRECT_IN,	// <
	TOKEN_REDIRECT_OUT,	// >
	TOKEN_APPEND,		// >>
	TOKEN_HEREDOC,		// <<
	TOKEN_ENV_VAR,		// $ for environment variables
	TOKEN_QUOTE,		// ' for single-quoted strings
	TOKEN_DQUOTE,		// " for double-quoted strings
	TOKEN_WHITESPACE,	// Spaces, tabs, etc.
	TOKEN_INVALID		// Invalid token, e.g., unrecognized characters
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
} t_token;


void	token_redidrect(char *input, t_token **token, int *i);
void	token_single_quote(char *input, t_token **token, int *i);
void	token_double_quote(char *input, t_token **token, int *i);
t_token	*tokenize(char *input);
t_token	*create_token(char *value, t_token_type type);
void	add_token(t_token **head, t_token *new_token);
int     is_whitespace(char c);
void	free_tokens(t_token *token);

#endif