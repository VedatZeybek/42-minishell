#include "../includes/minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,			// Regular command or argument
	TOKEN_PIPE,			// |
	TOKEN_REDIRECT_IN,	// <
	TOKEN_REDIRECT_OUT,	// >
	TOKEN_APPEND,		// >>
	TOKEN_HEREDOC,		// << for here documents
	TOKEN_ENV_VAR,		// $ for environment variables
	TOKEN_QUOTE,		// ' for single-quoted strings
	TOKEN_DQUOTE,		// " for double-quoted strings
	TOKEN_WHITESPACE,	// Spaces, tabs, etc.
	TOKEN_INVALID		// Invalid token, e.g., unrecognized characters
}	t_token_type;

typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '\r' || c == '\v' || c == '\f');
}

// cat out | grep "hello"
// com file.name pipe com literal

t_token	*tokenize(char *input)
{
	t_token	*token;
	int		i;

	i = 0;
	if (!input || !*input)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (input[i] == '|')
		{
			token->type = TOKEN_PIPE;
			continue ;
		}
		if (input[i] == '<')
		{
			token->type = TOKEN_REDIRECT_IN;
			i++;
			continue ;
		}
		if (input[i] == '>')
		{
			token->type = TOKEN_APPEND;
			i++;
			continue ;
		}
		if (input[i] == '$')
		{
			token->type = TOKEN_ENV_VAR;
			i++;
			continue ;
		}
		if (input[i] == '\'')
		{
			token->type = TOKEN_QUOTE;
			i++;
			continue ;
		}
	token->value = ft_strdup(input);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = TOKEN_WORD;
	return (token);
	}
}
