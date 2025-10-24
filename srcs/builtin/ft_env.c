/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:18:32 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 14:21:54 by vedat-zeybe      ###   ########.fr       */
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
