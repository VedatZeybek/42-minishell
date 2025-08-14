#include "../../includes/parser.h"

int add_to_argv(char ***argv, char *value)
{
	char **new_argv;
	int i;
	int	j;

	if (!argv || !value)
		return (0);
	if (!*argv)
	{
		*argv = malloc(2 * sizeof(char *));
		if (!*argv)
			return (0);
		(*argv)[0] = ft_strdup(value);
		(*argv)[1] = NULL;
		return (1);
	}
	i = 0;
	while ((*argv)[i])
		i++;
	new_argv = malloc((i + 2) * sizeof(char *));
	if (!new_argv)
		return (0);
	j = 0;
	while (j < i)
	{
		new_argv[j] = (*argv)[j];
		j++;
	}
	new_argv[i] = ft_strdup(value);
	new_argv[i + 1] = NULL;
	free(*argv);
	*argv = new_argv;
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

static void	parse_token_chunk(t_token **tmp, char ***argv, t_redir **redirs)
{
	if ((*tmp)->type == TOKEN_WORD)
		add_to_argv(argv, (*tmp)->value);
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
	char		**argv;

	if (!tokens || !*tokens)
		return (NULL);
	tmp = *tokens;
	argv = NULL;
	redirs = NULL;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		parse_token_chunk(&tmp, &argv, &redirs);
		tmp = tmp->next;
	}
	cmd = create_command(argv, redirs);
	if (tmp && tmp->type == TOKEN_PIPE && tmp->next)
		cmd->next = parse_command(&tmp->next);
	else
		cmd->next = NULL;
	return (cmd);
}
