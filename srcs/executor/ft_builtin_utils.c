/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:55:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 22:56:53 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

size_t	argv_length(t_command *cmd)
{
	size_t	len;

	len = 0;
	if (!cmd || !cmd->argv)
		return (0);
	while (cmd->argv[len].value != NULL)
		len++;
	return (len);
}

void	free_string_array(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
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
