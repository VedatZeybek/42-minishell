/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:18:32 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/16 11:12:52 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f(char *content)
{
	printf("%s\n", content);
}

int	ft_env(char **argv, t_list *env)
{
	if (arg_count(argv) != 1)
		return (printf("env: ‘%s’: No such file or directory", argv[1]), 1);
	ft_lstiter(env, (void *)f);
	return (0);
}
