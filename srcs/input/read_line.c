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

//char *remove_tabs(char *line)
//{
//    int i = 0, j = 0;
//    while (line[i])
//    {
//        if (line[i] != '\t')
//            line[j++] = line[i];
//        i++;
//    }
//    line[j] = '\0';
//    return line;
//}

int g_exit_status = 0;

void sigint_handler(int signo)
{
    (void)signo;
    g_exit_status = 130;  // $? için
    write(1, "\n", 1);
    rl_replace_line("", 0); // input temizlensin
    rl_on_new_line();       // readline’a yeni satır de
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
