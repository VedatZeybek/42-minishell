/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:18:32 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/04 10:29:47 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **argv, char **envp)
{
	int	i;

	if (ft_arg_count(argv) != 1)
		return (printf("env: '%s': No such file or directory\n", argv[1]), 1);
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (0);
}
