#include "../inc/minishell.h"

static void	sigint_handler()
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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
