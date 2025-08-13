#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


# define PROMPT "minishell$ "

# define ERR_INPUT "Invalid number of arguments."
# define ERR_FILE "Invalid File."
# define ERR_PATH "Path Not Found."
# define ERR_CMD "Command Not Found."
# define ERR_PRC "Process Failed."
# define ERR_PIPE "Pipe Creation Failed."
# define ERR_EXCVE "Execution Failed."
# define ERR_CLS "Close File Failed."

typedef struct s_shell
{
    int		running;
}	t_shell;

void	error(char *msg);
char	*read_line(void);
void	free_splitted(char **str);
//void	here_doc(char *limiter);
char	*get_cmd_path(char *cmd, char **envp);
void	execute_command(char *line, char **envp);

#endif