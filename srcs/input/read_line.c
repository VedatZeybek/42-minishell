/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:02 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 12:23:45 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sigint_handler(int signo)
{
	(void)signo;
	g_exit_status = 130;
	if (isatty(STDIN_FILENO))
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
char	*read_line(void)
{
	char			*line;
	char			*prompt;
	static char		*colors[12];
	static int		color_index = 0;
	int				n_colors;

	n_colors = 12;
	if (!colors[0])
	{
		colors[0] = RED;
		colors[1] = GREEN;
		colors[2] = YELLOW;
		colors[3] = BLUE;
		colors[4] = MAGENTA;
		colors[5] = CYAN;
		colors[6] = LIGHT_RED;
		colors[7] = LIGHT_GREEN;
		colors[8] = LIGHT_YELLOW;
		colors[9] = LIGHT_BLUE;
		colors[10] = LIGHT_MAGENTA;
		colors[11] = LIGHT_CYAN;
	}
	prompt = ft_strjoin(colors[color_index], "minishell$ ");
	prompt = ft_strjoin(prompt, RESET);

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);

	if (g_exit_status != 130)
		line = readline(prompt);
	else
		line = readline("");

	free(prompt);

	if (!line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (NULL);
	}
	if (*line)
		add_history(line);

	color_index++;
	if (color_index >= n_colors)
		color_index = 0;

	return (line);
}
