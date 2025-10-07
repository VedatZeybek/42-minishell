#include "../../includes/tokenizer.h"

void	token_redidrect(char *input, t_token **token, int *i)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			add_token(token, create_token(">>", TOKEN_APPEND));
			*i += 2;
		}
		else
		{
			add_token(token, create_token(">", TOKEN_REDIRECT_OUT));
			(*i)++;
		}
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			add_token(token, create_token("<<", TOKEN_HEREDOC));
			*i += 2;
		}
		else
		{
			add_token(token, create_token("<", TOKEN_REDIRECT_IN));
			(*i)++;
		}
	}
}