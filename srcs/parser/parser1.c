#include "../../includes/parser.h"

t_command *create_command(char **argv, char **redirections)
{
	t_command *cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = argv;
	cmd->redirections = redirections;
	cmd->next = NULL;
	return (cmd);
}

void add_command(t_command **head, t_command *new_cmd)
{
	t_command *current;

	if (!head || !new_cmd)
		return ;
	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

void free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	free_splitted(cmd->argv);
	free_splitted(cmd->redirections);
	free(cmd);
}

