#include "./includes/minishell.h"

t_token	*tokenize(char *input)
{
	t_token	*token;
	int		i;
	int		start;

	i = 0;
	token = NULL;
	if (!input || !*input)
		return (NULL);
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (input[i] == '\'')
		{
			token_single_quote(input, &token, &i);
			continue ;
		}
		if (input[i] == '"')
		{
			token_double_quote(input, &token, &i);
			continue ;
		}
		if (input[i] == '|')
		{
			add_token(&token, create_token("|", TOKEN_PIPE));
			i++;
			continue ;
		}
		if (input[i] == '$')
		{
			start = i++;
			while (isalnum(input[i]) || input[i] == '_') i++;
			add_token(&token, create_token(strndup(input + start, i - start), TOKEN_ENV_VAR));
			continue ;
		}
		if (input[i] == '>' || input[i] == '<')
		{
			token_redidrect(input, &token, &i);
			continue ;
		}
		start = i;
		while (input[i] && !is_whitespace(input[i]) && input[i] != '|' &&
				input[i] != '<' && input[i] != '>')
			i++;
		if (i > start)
		{
			add_token(&token, create_token(input + start, TOKEN_WORD));
			continue ;
		}
		if (input[i] != '\0')
		{
			perror("minishell: invalid character\n");
			free(token);
			return (NULL);
		}
	}
	return (token);
}