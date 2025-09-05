/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:02 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/13 19:12:25 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int g_exit_status = 0;

void sigint_handler(int signo)
{
	(void)signo;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay(); 
}

char	*read_line(void)
{
	char	*line;
	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline(PROMPT);
	if (!line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}
