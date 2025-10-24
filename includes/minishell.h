/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:22:57 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 23:07:00 by vedat-zeybe      ###   ########.fr       */
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
# include "ft_builtin.h"
# include "libft.h"
# include "tokenizer.h"
# include "parser.h"

# define RED        "\001\033[0;31m\002"
# define GREEN      "\001\033[0;32m\002"
# define YELLOW     "\001\033[0;33m\002"
# define BLUE       "\001\033[0;34m\002"
# define MAGENTA    "\001\033[0;35m\002"
# define CYAN       "\001\033[0;36m\002"
# define LIGHT_RED  "\001\033[91m\002"
# define LIGHT_GREEN "\001\033[92m\002"
# define LIGHT_YELLOW "\001\033[93m\002"
# define LIGHT_BLUE "\001\033[94m\002"
# define LIGHT_MAGENTA "\001\033[95m\002"
# define LIGHT_CYAN "\001\033[96m\002"
# define RESET      "\001\033[0m\002"

# define ERR_INPUT "Invalid number of arguments."
# define ERR_FILE "Invalid File."
# define ERR_PATH "Path Not Found."
# define ERR_CMD "Command Not Found."
# define ERR_PRC "Process Failed."
# define ERR_PIPE "Pipe Creation Failed."
# define ERR_EXCVE "Execution Failed."
# define ERR_CLS "Close File Failed."

extern int	g_exit_status;

typedef struct s_shell
{
	int			running;
}		t_shell;

char	*read_line(void);
void	free_splitted(char **str);

#endif
