/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:22:15 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/25 14:22:15 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

static	int	free_result(char **result, int i)
{
	int	j;

	j = 0;
	if (!result[i])
	{
		while (j < i)
		{
			free(result[j]);
			j++;
		}
		free(result);
		return (1);
	}
	return (0);
}

char	**copy_argv_to_string_array(t_command *cmd, size_t argv_len)
{
	char	**result;
	size_t	i;

	if (!cmd || !cmd->argv || argv_len == 0)
		return (NULL);
	result = malloc((argv_len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < argv_len)
	{
		result[i] = ft_strdup(cmd->argv[i].value);
		if (free_result(result, i) == 1)
			return (NULL);
		i++;
	}
	result[argv_len] = NULL;
	return (result);
}
