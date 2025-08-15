/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:12:01 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/15 21:04:47 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	char	cwd[PATH_MAX];

	if (arg_count(args) != 1)
		return (printf("pwd: too many arguments\n"), 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd hatası");
	return (0);
}
