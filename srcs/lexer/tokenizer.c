#include "../../includes/tokenizer.h"

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

static int	process_token(char *input, t_token **token, int *i)
{
	if (handle_operators(input, token, i))
		return (1);
	if (handle_word(input, token, i))
		return (1);
	if (input[*i] && !is_whitespace(input[*i]))
	{
		printf("minishell: unexpected character '%c'\n", input[*i]);
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