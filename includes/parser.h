#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

typedef struct s_args
{
	t_token_type	type;
	char			*value;
}	t_arg;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	t_arg			*argv;
	t_redir			*redirections;
	struct s_command *next;
} t_command;

void	free_command(t_command *cmd);
t_command	*create_command(t_arg *args, t_redir *redirections);
void		add_command(t_command **head, t_command *new_cmd);
t_command	*parse_command(t_token **tokens);

#endif