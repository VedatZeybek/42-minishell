#include "../../includes/minishell.h"

static int	handle_special_chars(char *input, t_token **token, int *i)
{
	int	start;

	if (input[*i] == '\'')
	{
		token_single_quote(input, token, i);
		return (1);
	}
	if (input[*i] == '"')
	{
		token_double_quote(input, token, i);
		return (1);
	}
	if (input[*i] == '$')
	{
		start = *i;
		(*i)++;
		while (ft_isalnum(input[*i]) || input[*i] == '_')
			(*i)++;
		add_token(token, create_token(strndup(input + start, *i - start),
				TOKEN_ENV_VAR));
		return (1);
	}
	return (0);
}

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
		token_redidrect(input, token, i);
		return (1);
	}
	return (0);
}

static int	handle_word(char *input, t_token **token, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>' && input[*i] != '\''
		&& input[*i] != '"' && input[*i] != '$')
		(*i)++;
	if (*i > start)
	{
		add_token(token, create_token(strndup(input + start, *i - start),
				TOKEN_WORD));
		return (1);
	}
	return (0);
}

static int	process_token(char *input, t_token **token, int *i)
{
	if (handle_special_chars(input, token, i))
		return (1);
	if (handle_operators(input, token, i))
		return (1);
	if (handle_word(input, token, i))
		return (1);
	printf("minishell: unexpected character '%c'\n", input[*i]);
	free_tokens(*token);
	return (0);
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


