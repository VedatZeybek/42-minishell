/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:55:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 15:07:04 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

size_t argv_length(t_command *cmd)
{
    if (!cmd || !cmd->argv)
        return 0;

    size_t len = 0;
    while (cmd->argv[len].value != NULL)
        len++;
    return len;
}

char **copy_argv_to_string_array(t_command *cmd, size_t argv_len)
{
    if (!cmd || !cmd->argv || argv_len == 0)
        return NULL;

    char **arr = malloc((argv_len + 1) * sizeof(char *)); // +1 NULL için
    if (!arr)
        return NULL;

    for (size_t i = 0; i < argv_len; i++)
    {
        arr[i] = strdup(cmd->argv[i].value);
        if (!arr[i])
        {
            // malloc hatası, temizle
            for (size_t j = 0; j < i; j++)
                free(arr[j]);
            free(arr);
            return NULL;
        }
    }
    arr[argv_len] = NULL; // sonlandırıcı NULL
    return arr;
}

void free_string_array(char **arr)
{
    if (!arr) return;
    for (size_t i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}


int	ft_check_builtin(const char *c, const char *b)
{
	int	tmp;

	if (!c || !b)
		return (0);
	tmp = ft_strncmp(c, b, ft_strlen(b) + 1);
	if (tmp == 0)
		return (1);
	return (0);
}

int	ft_call_builtin(t_command *cmd, char **envp)
{
	char	**str;

	str = copy_argv_to_string_array(cmd, argv_length(cmd));
	if (ft_check_builtin(cmd->argv[0].value, "echo"))
		return (ft_echo(str));
	else if (ft_check_builtin(cmd->argv[0].value, "cd"))
		return (ft_cd(str));
	else if (ft_check_builtin(cmd->argv[0].value, "pwd"))
		return (ft_pwd(str));
	else if (ft_check_builtin(cmd->argv[0].value, "env"))
		return (ft_env(str, envp));
	return (0);
}
