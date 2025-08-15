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


char	*remove_quotes(const char *str);



void	expand_command(t_command *command)
{
	int		i;
	char	*no_quotes;

	if (!command || !command->argv)
		return;
	i = 0;
	while (command)
	{
		while (command->argv[i])
		{
			if (command->argv)
			{

			}
		}
	}
	
}


char	*remove_quotes(const char *str)
{
	int	len;
	char	*res;
	int i;
	int	j;

	i = 0;
	j = 0;
	len = strlen(str);
	res = malloc(len + 1);
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return res;
}