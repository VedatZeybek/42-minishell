#include "../../includes/minishell.h"

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

void	token_single_quote(char *input, t_token **token, int *i)
{
	int	start;

	start = ++(*i);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
	{
		add_token(token, create_token(strndup(input + start, *i - start), TOKEN_QUOTE));
		(*i)++;
	}
	else
	{
		perror("minishell: unclosed single quote\n");
		free(*token);
		*token = NULL;
	}
}

void	token_double_quote(char *input, t_token **token, int *i)
{
	int	start;

	start = ++(*i);
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (input[*i] == '"')
	{
		add_token(token, create_token(strndup(input + start, *i - start), TOKEN_DQUOTE));
		(*i)++;
	}
	else
	{
		perror("minishell: unclosed double quote\n");
		free(*token);
		*token = NULL;
	}
}
