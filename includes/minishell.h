/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:22:57 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 13:34:19 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "builtin.h"
# include "libft.h"
# include "tokenizer.h"
# include "parser.h"

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
	int	running;
}		t_shell;

extern int g_exit_status;

void	error(char *msg);
char	*read_line(void);
void	free_splitted(char **str);

#endif