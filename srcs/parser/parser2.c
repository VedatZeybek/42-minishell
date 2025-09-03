#include "../../includes/parser.h"

t_command	*create_command(t_arg *args, t_redir *redirections)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = args;
	cmd->redirections = redirections;
	cmd->next = NULL;
	return (cmd);
}

void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*current;

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

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	// args freelenecek
	// redirection freelenecek
	free(cmd);
}


//tokenizer -> echo "selam" | wc -l > output.txt 
	       //  W      DQ    P  W   R_OUT  W

		   // "$home " "selam lm ls "

// parser ->  command[echo "selam" ] | echo [wc -l > output.txt ]
		      // linked_list node      linked_list node
