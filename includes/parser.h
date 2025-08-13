#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_command
{
	char				**argv;	// Command arguments
	char				**redirections; // For input/output redirection
	struct s_command	*next; 	// Pointer to the next command in the pipeline
}	t_command;



#endif