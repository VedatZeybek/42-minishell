#include "../includes/minishell.h"

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
} t_token_type;


typedef struct s_token
{
    char *value;
    int type;
} t_token;

t_token *tokenize(char *input)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    
    token->value = strdup(input);
    if (!token->value)
    {
        free(token);
        return NULL;
    }
    
    token->type = TOKEN_WORD;
    return token;
}
