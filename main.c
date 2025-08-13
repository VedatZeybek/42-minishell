#include "./inc/minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_shell shell;
	char	*line;

	shell.running = 1;
	while (shell.running)
	{
		line = read_line();
		if (!line)
			break ;
		execute_command(line, env);
		free(line);
	}
	return (0);
}
