/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:21:28 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/25 14:21:29 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int signo)
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

static void	init_colors(char **colors)
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

static char	*create_prompt(char *color)
{
	char	*temp;
	char	*prompt;

	temp = ft_strjoin(color, "minishell$ ");
	prompt = ft_strjoin(temp, RESET);
	free(temp);
	return (prompt);
}

char	*read_line(void)
{
	char			*line;
	char			*prompt;
	static char		*colors[12];
	static int		color_index = 0;

	if (!colors[0])
		init_colors(colors);
	prompt = create_prompt(colors[color_index]);
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
	color_index = (color_index + 1) % 12;
	return (line);
}
