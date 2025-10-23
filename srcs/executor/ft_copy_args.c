#include "../../includes/ft_executor.h"


char **copy_argv_to_string_array(t_command *cmd, size_t argv_len)
{
	if (!cmd || !cmd->argv || argv_len == 0)
		return NULL;

	char **arr = malloc((argv_len + 1) * sizeof(char *));
	if (!arr)
		return NULL;

	for (size_t i = 0; i < argv_len; i++)
	{
		arr[i] = ft_strdup(cmd->argv[i].value);
		if (!arr[i])
		{
			for (size_t j = 0; j < i; j++)
				free(arr[j]);
			free(arr);
			return NULL;
		}
	}
	arr[argv_len] = NULL;
	return arr;
}
