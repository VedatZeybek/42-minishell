#include "../../includes/parser.h"

int add_arg(t_arg **args, char *value, t_token_type type)
{
	t_arg	*new_args;
	int		i;
	int		j;

	if (!value || !args)
		return (0);
	i = 0;
	j = 0;
	if (*args)
		while ((*args)[i].value)
		i++;
	new_args = malloc((i + 2) * sizeof(t_arg));
	if (!new_args)
		return (0);
	if (*args)
	{
		while (j < i)
		{
			new_args[j] = (*args)[j];
			j++;
		}
		free(*args);
	}
	new_args[i].value = ft_strdup(value);
	new_args[i].type = type;
	new_args[i + 1].value = NULL;
	new_args[i + 1].type = 0;
	*args = new_args;
	return (1);
}

int	add_to_redirections(t_redir **list, t_token_type type, char *filename)
{
	t_redir	*new_node;
	t_redir	*tmp;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (0);
	new_node->type = type;
	new_node->filename = ft_strdup(filename);
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (1);
}

static void	parse_token_chunk(t_token **tmp, t_arg **args, t_redir **redirs)
{
	if ((*tmp)->type == TOKEN_WORD
		|| (*tmp)->type == TOKEN_QUOTE
		|| (*tmp)->type == TOKEN_DQUOTE
		|| (*tmp)->type == TOKEN_ENV_VAR)
		add_arg(args, (*tmp)->value, (*tmp)->type);
	else if ((*tmp)->type == TOKEN_REDIRECT_IN
		|| (*tmp)->type == TOKEN_REDIRECT_OUT
		|| (*tmp)->type == TOKEN_APPEND
		|| (*tmp)->type == TOKEN_HEREDOC)
	{
		if ((*tmp)->next)
		{
			add_to_redirections(redirs, (*tmp)->type, (*tmp)->next->value);
			*tmp = (*tmp)->next;
		}
	}
}

t_command	*parse_command(t_token **tokens)
{
	t_command	*cmd;
	t_token		*tmp;
	t_redir		*redirs;
	t_arg		*args;

	if (!tokens || !*tokens)
		return (NULL);
	tmp = *tokens;
	args = NULL;
	redirs = NULL;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		parse_token_chunk(&tmp, &args, &redirs);
		tmp = tmp->next;
	}
	cmd = create_command(args, redirs);
	if (tmp && tmp->type == TOKEN_PIPE && tmp->next)
		cmd->next = parse_command(&tmp->next);
	else
		cmd->next = NULL;
	return (cmd);
}
