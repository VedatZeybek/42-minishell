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

	// argv dizisini free et
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i].value) // argv dizisinin sonu NULL değilse dikkat
		{
			if (cmd->argv[i].value)
				free(cmd->argv[i].value);
			i++;
		}
		free(cmd->argv);
	}

	// redirections linked list
	if (cmd->redirections)
		free_redirs(cmd->redirections);

	free(cmd);
}



//tokenizer -> echo "selam" | wc -l > output.txt 
	       //  W      DQ    P  W   R_OUT  W

		   // "$home " "selam lm ls "

// parser ->  command[echo "selam" ] | echo [wc -l > output.txt ]
		      // linked_list node      linked_list node
