#include "../../includes/ft_executor.h"

static char	**ft_init_env(char **envp)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			res = ft_split(ft_strchr(envp[i], '=') + 1, ':');
			break ;
		}
		i++;
	}
	return (res);
}

char	**ft_env_dup(char **envp)
{
    char	**dup;
    int		len;
	int		i;

	i = 0;
	len = ft_env_len(envp);
	dup = malloc(sizeof(char *) * (len + 1));
    if (!dup)
        return NULL;
    while (i < len)
	{
        dup[i] = ft_strdup(envp[i]);
		i++;
	}
    dup[len] = NULL;
    return dup;
}

void	ft_init_vars(t_vars *vars, char **envp)
{
	vars->envp = ft_env_dup(envp);
	vars->path = ft_init_env(envp);
}

void	ft_free_vars(t_vars *vars)
{
	int i;

	if (!vars)
		return;
	if (vars->envp)
	{
		i = 0;
		while (vars->envp[i])
		{
			free(vars->envp[i]);
			i++;
		}
		free(vars->envp);
		vars->envp = NULL;
	}
	if (vars->path)
	{
		i = 0;
		while (vars->path[i])
		{
			free(vars->path[i]);
			i++;
		}
		free(vars->path);
		vars->path = NULL;
	}
}
