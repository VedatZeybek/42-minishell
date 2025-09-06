#include "../../includes/minishell.h"

int is_numeric(const char *str);

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

int ft_exit(char **args)
{
    int exit_code = 0;

    if (args[1])
    {
        if (!is_numeric(args[1]))
        {
            printf("exit\n");
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[1]);
            exit(255);
        }
        exit_code = ft_atoi(args[1]);
        if (args[2])
        {
            fprintf(stderr, "minishell: exit: too many arguments\n");
            g_exit_status = 1;
            return (1);
        }
    }

    printf("exit\n");
    exit((unsigned char)exit_code);
}

int is_numeric(const char *str)
{
    int i = 0;

    if (!str || str[0] == '\0')
        return 0; // boş string numeric değil

    // Opsiyonel baştaki + veya -
    if (str[i] == '+' || str[i] == '-')
        i++;

    // En az bir rakam olmalı
    if (!str[i])
        return 0;

    while (str[i])
    {
        if (!ft_isdigit((unsigned char)str[i]))
            return 0; // rakam olmayan karakter var
        i++;
    }
    return 1; // tamamen rakamlardan oluşuyor
}