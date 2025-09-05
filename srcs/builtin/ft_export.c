#include "../../includes/ft_executor.h"

char *ft_strjoin3(char *s1, char *s2, char *s3)
{
	if (!s1 || !s2 || !s3)
		return NULL;
	size_t len1 = ft_strlen(s1);
	size_t len2 = ft_strlen(s2);
	size_t len3 = ft_strlen(s3);
	char *res = malloc(len1 + len2 + len3 + 1);
	if (!res)
		return NULL;
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	ft_memcpy(res + len1 + len2, s3, len3);
	res[len1 + len2 + len3] = '\0';
	return res;
}

char **ft_realloc_add(char **arr, char *new_str)
{
	int i = 0;
	while (arr && arr[i])
		i++;

	char **new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return NULL;

	for (int j = 0; j < i; j++)
		new_arr[j] = arr[j];

	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;

	free(arr);
	return new_arr;
}

char *ft_get_env(t_vars *vars, char *key)
{
	if (!vars || !key)
		return NULL;

	size_t klen = ft_strlen(key);
	for (int i = 0; vars->envp && vars->envp[i]; i++)
	{
		size_t elen = ft_strlen(vars->envp[i]);
		if (elen > klen && ft_strncmp(vars->envp[i], key, klen) == 0
			&& vars->envp[i][klen] == '=')
		{
			return vars->envp[i] + klen + 1;
		}
	}
	return NULL;
}

void ft_set_env(t_vars *vars, char *key, char *value)
{
	if (!vars || !key || !value)
		return;

	size_t klen = ft_strlen(key);
	for (int i = 0; vars->envp && vars->envp[i]; i++)
	{
		size_t elen = ft_strlen(vars->envp[i]);
		if (elen > klen && ft_strncmp(vars->envp[i], key, klen) == 0
			&& vars->envp[i][klen] == '=')
		{
			char *tmp = ft_strjoin3(key, "=", value);
			if (!tmp)
				return;
			free(vars->envp[i]);
			vars->envp[i] = tmp;
			return;
		}
	}
	char *new_env = ft_strjoin3(key, "=", value);
	if (!new_env)
		return;
	vars->envp = ft_realloc_add(vars->envp, new_env);
}

int ft_export(t_vars *vars, char **args)
{
	if (!vars || !args)
		return 1;

	printf("first len: %d\n", 	ft_env_len(vars->envp));

	for (int i = 1; args[i]; i++)
	{
		char *eq = strchr(args[i], '=');

		if (eq)
		{
			*eq = '\0';
			ft_set_env(vars, args[i], eq + 1);
		}
	}
	printf("second len: %d\n", 	ft_env_len(vars->envp));
	return 0;
}
