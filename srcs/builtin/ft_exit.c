#include "../../includes/minishell.h"

int	ft_exit_child(char **args)
{
	int exit_code = 0;

	if (args[1])
	{
		// Eğer parametre sayı değilse hata ver
		exit_code = atoi(args[1]); // basit hali, daha güvenli atoi ile yapabilirsin
		if (exit_code < 0)
		{
			printf("exit: numeric argument required\n");
			exit_code = 255;
		}
	}
	//printf("exit\n"); // Minishell’de genellikle exit yazdırılır
	return(exit_code); // shell’i kapat
}

int	ft_exit(char **args)
{
	int exit_code = 0;

	if (args[1])
	{
		// Eğer parametre sayı değilse hata ver
		exit_code = atoi(args[1]); // basit hali, daha güvenli atoi ile yapabilirsin
		if (exit_code < 0)
		{
			printf("exit: numeric argument required\n");
			exit_code = 255;
		}
	}
	printf("exit\n"); // Minishell’de genellikle exit yazdırılır
	exit(exit_code); // shell’i kapat
}