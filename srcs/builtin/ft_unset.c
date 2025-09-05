#include "../../includes/ft_executor.h"

int ft_env_len(char **envp)
{
    int i = 0;
    while (envp && envp[i])
        i++;
    return i;
}

void ft_remove_env(t_vars *vars, char *key)
{
	int i = 0, j = 0;
	size_t len = ft_strlen(key);
	char **new_env = malloc(sizeof(char *) * (ft_env_len(vars->envp)));
	while (vars->envp[i])
	{
		if (!(ft_strncmp(vars->envp[i], key, len) == 0 && vars->envp[i][len] == '='))
			new_env[j++] = vars->envp[i];
		else
			free(vars->envp[i]);
		i++;
	}
	new_env[j] = NULL;
	free(vars->envp);
	vars->envp = new_env;
}

int ft_unset(t_vars *vars, char **args)
{
	int i = 1;
	while (args[i])
	{
		ft_remove_env(vars, args[i]);
		i++;
	}
	return 0;
}
