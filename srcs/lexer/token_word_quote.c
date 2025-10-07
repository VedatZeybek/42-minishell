#include "../../includes/minishell.h"

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

int	handle_word(char *input, t_token **token, int *i)
{
	char	*buffer;
	int		start_i;

	buffer = ft_strdup("");
	start_i = *i;
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
	if (*i > start_i)
		return (1);
	return (0);
}
