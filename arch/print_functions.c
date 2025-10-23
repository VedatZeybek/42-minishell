#include "minishell.h"

void print_tokens(t_token *tokens)
{
	t_token *tmp = tokens;
	while (tmp)
	{
		printf("Token: '%s', Type: %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}

void	print_command(t_command *cmd)
{
	int	i;
	t_redir	*redir;

	while (cmd)
	{
		printf("=== COMMAND ===\n");
		i = 0;
		while (cmd->argv && cmd->argv[i].value)
		{
			printf("  argv[%d] = \"%s\" (type = %d)\n",
				i, cmd->argv[i].value, cmd->argv[i].type);
			i++;
		}
		redir = cmd->redirections;
		while (redir)
		{
			printf("  redir: type = %d, filename = \"%s\"\n",
				redir->type, redir->filename);
			redir = redir->next;
		}
		if (cmd->next)
			printf("  |\n  v\n");
		cmd = cmd->next;
	}
}
