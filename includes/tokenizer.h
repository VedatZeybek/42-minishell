#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,			// 0 Regular command or argument
	TOKEN_PIPE,			// 1 | 
	TOKEN_REDIRECT_IN,	// 2 <
	TOKEN_REDIRECT_OUT,	// 3 >
	TOKEN_APPEND,		// 4 >>
	TOKEN_HEREDOC,		// 5 <<
	TOKEN_ENV_VAR,		// 6 $ for environment variables
	TOKEN_QUOTE,		// 7 ' for single-quoted strings
	TOKEN_DQUOTE,		// 8 " for double-quoted strings
	TOKEN_WHITESPACE,	// 9 Spaces, tabs, etc.
	TOKEN_INVALID		// 10 Invalid token, e.g., unrecognized characters
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
int		is_whitespace(char c);
void	free_tokens(t_token *token);

#endif