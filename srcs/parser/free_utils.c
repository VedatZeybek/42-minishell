#include "../../includes/parser.h"

static void	free_redirs(t_redir *redir)
{
	t_redir *tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_command(t_command *cmd)
{
	int i;

	if (!cmd)
		return ;

	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i].value)
		{
			if (cmd->argv[i].value)
				free(cmd->argv[i].value);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->redirections)
		free_redirs(cmd->redirections);
	free(cmd);
}

