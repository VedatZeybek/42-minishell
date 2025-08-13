#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_command
{
	char				**argv;	// Command arguments
	char				**redirections; // For input/output redirection
	struct s_command	*next; 	// Pointer to the next command in the pipeline
}	t_command;

typedef struct s_redir {
	t_token_type	type;      // TOKEN_REDIRECT_OUT, TOKEN_APPEND, vb.
	char			*filename; // tmp->next->value
	struct s_redir	*next;
}	t_redir;


void	free_command(t_command *cmd);
t_command	*create_command(char **argv, char **redirections);
void	add_command(t_command **head, t_command *new_cmd);
t_command	*parse_command(t_token **tokens);

#endif