////#include "../../includes/minishell.h"

////// "ls -la" | grep libft | "cat -e " > put

////// BU KOMUTU ÇALIŞTIRDIĞINDA OLUŞACAK  T_COMMAND YAPISI:

//////t_command: "ls -la"
//////argv: ["ls -la", NULL]
//////redirections: NULL
//////next ──> t_command: grep libft
//////            argv: ["grep", "libft", NULL]
//////            redirections: NULL
//////            next ──> t_command: "cat -e "
//////                        argv: ["cat -e ", NULL]
//////                        redirections: TOKEN_REDIRECT_OUT -> "put" -> NULL
//////                        next: NULL

////// This function expands the command arguments in a t_command structure.
////// It should handle environment variables, quotes, and other expansions as needed.

//////commandları ayrı, argları ayrı, redirectionları ayrı expand etmek lazım


////input:


////typedef struct s_redir {
////	t_token_type	type;      // TOKEN_REDIRECT_OUT, TOKEN_APPEND, vb.
////	char			*filename; // tmp->next->value
////	struct s_redir	*next;
////}	t_redir;

////typedef struct s_command
////{
////	char				**argv;	// Command arguments
////	t_redir				*redirections; // For input/output redirection
////	struct s_command	*next; 	// Pointer to the next command in the pipeline
////}	t_command;

//void	expand_args(char **argv)
//{
//	char	**expanded;
//	char	**splitted;
//	int		i;

//	while (argv[i])
//	{
//		splitted = ft_split(argv, ' ');
		
	
//	}
//}



//////command expansion -> expand + split

////void	expand_command(t_command *command_list)
////{
////	t_command	*command;
////	char		*no_quotes;
////	char		**splitted;
////	char		**new_argv;
////	int			i;

////	command = command_list;
////	if (!command || !command->argv)
////		return ;
////	while (command)
////	{
////		new_argv = NULL;
////		i = 0;
////		while (command->argv && command->argv[i])
////		{
////			no_quotes = command->argv[i];
////			splitted = ft_split(no_quotes, ' ');
////			i++;
////		}
////		command = command->next;
////	}
////}

////char	*remove_quotes(const char *str)
////{
////	char	*res;
////	int		len;
////	int		i;
////	int		j;

////	i = 0;
////	j = 0;
////	len = strlen(str);
////	res = malloc(len + 1);
////	while (str[i])
////	{
////		if (str[i] != '"' && str[i] != '\'')
////		{
////			res[j] = str[i];
////			j++;
////		}
////		i++;
////	}
////	res[j] = '\0';
////	return (res);
////}

////char	*expand_env_var(char *str, char **envp)
////{
////	char	*var;
////	int		i;

////	i = 0;
////	if (str[0] != '$')
////		return (ft_strdup(str));
////	var = str + 1;

////	//GLOBAL DEĞİŞKENDE EXIT STATUS TUTULACAK

////	//if (str[1] == '?')
////	//	return (ft_itoa(g_exit_status)));,

////	while (envp[i])
////	{
////		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0
////			&& envp[i][ft_strlen(var)] == '=')
////			return (ft_strdup(envp[i] + strlen(var) + 1));
////		i++;
////	}
////	return (ft_strdup(""));
////}

//////// $VAR'ı çevirmek için
//////char *expand_env_var(const char *str, char **envp)
//////{
//////    if (str[0] != '$')
//////        return strdup(str);

//////    const char *var = str + 1; // $ işaretinden sonrası
//////    for (int i = 0; envp[i]; i++)
//////    {
//////        if (strncmp(envp[i], var, strlen(var)) == 0 && envp[i][strlen(var)] == '=')
//////            return strdup(envp[i] + strlen(var) + 1);
//////    }
//////    return strdup(""); // bulunamazsa boş string
//////}