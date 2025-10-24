#include "../../includes/ft_builtin.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char *joined;
	char *result;

	joined = ft_strjoin_free(s1, s2);
	result = ft_strjoin_free(joined, s3);
	return (result);
}

char	**ft_realloc_add(char **arr, char *new_str)
{
	int		i;
	char	**new_arr;
	int		j;

	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = new_str;
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}

int	ft_is_valid_input(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (arg[0] == '=')
		return (0);
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}