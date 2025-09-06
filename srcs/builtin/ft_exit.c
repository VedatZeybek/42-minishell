#include "../../includes/minishell.h"

int	ft_exit_child(char **args)
{
	int exit_code = 0;

	if (args[1])
	{
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0)
		{
			printf("exit: numeric argument required\n");
			exit_code = 255;
		}
	}
	return(exit_code);
}

int	ft_exit(char **args)
{
	int exit_code = 0;

	if (args[1])
	{
		exit_code = ft_atoi(args[1]);
		if (exit_code < 0)
		{
			printf("exit: numeric argument required\n");
			exit_code = 255;
		}
	}
	printf("exit\n");
	exit(exit_code);
}