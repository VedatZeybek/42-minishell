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
	char	**splitted;

	if (!command || !command->argv)
		return ;
	i = 0;
	while (command)
	{
		while (command->argv[i])
		{
			if (command->argv[i])
			{

			}
		}
	}
}

char	*remove_quotes(const char *str)
{
	char	*res;
	int		len;
	int		i;
	int		j;

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
	return (res);
}

char	*expand_env_var(char *str, char **envp)
{
	char	*var;
	int		i;

	i = 0;
	if (str[0] != '$')
		return (ft_strdup(str));
	var = str + 1;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
			&& envp[i][ft_strlen(var)] == '=')
			return (ft_strdup(envp[i] + strlen(var) + 1));
		i++;
	}
	return (ft_strdup("")); 
}

//// $VAR'ı çevirmek için
//char *expand_env_var(const char *str, char **envp)
//{
//    if (str[0] != '$')
//        return strdup(str);

//    const char *var = str + 1; // $ işaretinden sonrası
//    for (int i = 0; envp[i]; i++)
//    {
//        if (strncmp(envp[i], var, strlen(var)) == 0 && envp[i][strlen(var)] == '=')
//            return strdup(envp[i] + strlen(var) + 1);
//    }
//    return strdup(""); // bulunamazsa boş string
//}