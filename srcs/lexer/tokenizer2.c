#include "./includes/minishell.h"

t_token	*tokenize(char *input)
{
	t_token	*token;
	int		i;
	int		start;

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
			add_token(&token, create_token("|", TOKEN_PIPE));
			i++;
			continue ;
		}
		if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_token(&token, create_token("<<", TOKEN_HEREDOC));
				i += 2;
				continue ;
			}
			else
			{
				add_token(&token, create_token("<", TOKEN_REDIRECT_IN));
				i ++;
				continue ;
			}
		}
		if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_token(&token, create_token(">>", TOKEN_APPEND));
				i += 2;
				continue ;
			}
			else
			{
				add_token(&token, create_token(">", TOKEN_REDIRECT_OUT));
				i++;
				continue ;
			}
		}
		start = i;
		while (input[i] && !is_whitespace(input[i]) && input[i] != '|' &&
				input[i] != '<' && input[i] != '>')
			i++;
		if (i > start)
			add_token(&token, create_token(input + start, TOKEN_WORD));
	}
	return (token);
}
