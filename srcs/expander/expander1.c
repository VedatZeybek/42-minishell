#include "../../includes/minishell.h"

// "ls -la" | grep libft | "cat -e " > put

// BU KOMUTU ÇALIŞTIRDIĞINDA OLUŞACAK  T_COMMAND YAPISI:

//t_command: "ls -la"
//argv: ["ls -la", NULL]
//redirections: NULL
//next ──> t_command: grep libft
//            argv: ["grep", "libft", NULL]
//            redirections: NULL
//            next ──> t_command: "cat -e "
//                        argv: ["cat -e ", NULL]
//                        redirections: TOKEN_REDIRECT_OUT -> "put" -> NULL
//                        next: NULL

// This function expands the command arguments in a t_command structure.
// It should handle environment variables, quotes, and other expansions as needed.


void	expand_command(t_command *command)
{
	int		i;

	if (!command || !command->argv)
		return;
	i = 0;
	while (command->argv[i])
	{

	}
}