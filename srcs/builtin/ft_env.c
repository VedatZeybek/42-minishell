/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:18:32 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/15 11:58:03 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **argv, char **envp)
{
	int	i;

	if (arg_count(argv) != 1)
		return (printf("env: ‘%s’: No such file or directory\n", argv[1]), 1);
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (0);
}
