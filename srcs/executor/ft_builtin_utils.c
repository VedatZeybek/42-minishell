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

