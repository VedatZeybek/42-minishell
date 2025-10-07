#include "../../includes/minishell.h"

static void append_env_var(char **buffer, char *input, int *i);


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

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static void	append_single_quote(char **buffer, char *input, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	*buffer = ft_strjoin_free(*buffer, ft_substr(input, start, *i - start));
	if (input[*i] == '\'')
		(*i)++;
}

static void append_double_quote(char **buffer, char *input, int *i)
{
	int start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			if (*i > start)
				*buffer = ft_strjoin_free(*buffer, ft_substr(input, start, *i - start));
			append_env_var(buffer, input, i);
			start = *i;
		}
		else
			(*i)++;
	}
	if (*i > start)
		*buffer = ft_strjoin_free(*buffer, ft_substr(input, start, *i - start));
	if (input[*i] == '"')
		(*i)++;
}


static void append_env_var(char **buffer, char *input, int *i)
{
	char    *var_name;
	char    *value;
	int     start;

	(*i)++;
	if (input[*i] == '?')
	{
		value = ft_itoa(g_exit_status);
		*buffer = ft_strjoin_free(*buffer, value);
		free(value);
		(*i)++;
		return ;
	}
	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (*i == start)
	{
		*buffer = ft_strjoin_free(*buffer, "$");
		return ;
	}
	var_name = ft_substr(input, start, *i - start);
	value = getenv(var_name);
	if (value && value[0] != '\0')
    	*buffer = ft_strjoin_free(*buffer, value);
	free(var_name);
}


static int	handle_word(char *input, t_token **token, int *i)
{
	char	*buffer;

	buffer = ft_strdup("");
	while (input[*i] && !is_whitespace(input[*i])
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'')
			append_single_quote(&buffer, input, i);
		else if (input[*i] == '"')
			append_double_quote(&buffer, input, i);
		else if (input[*i] == '$')
			append_env_var(&buffer, input, i);
		else
		{
			char temp[2] = {input[*i], '\0'};
			buffer = ft_strjoin_free(buffer, temp);
			(*i)++;
		}
	}
	if (ft_strlen(buffer) > 0)
	{
		add_token(token, create_token(buffer, TOKEN_WORD));
		free(buffer);
		return (1);
	}
	free(buffer);
	return (0);
}


static int	process_token(char *input, t_token **token, int *i)
{
	if (handle_operators(input, token, i))
		return (1);
	if (handle_word(input, token, i))
		return (1);
	if (input[*i] == '\0' || input[*i])
	{
		add_token(token, create_token("", TOKEN_WORD));
		return (1);
	}
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
