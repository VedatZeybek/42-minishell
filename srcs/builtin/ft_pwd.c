/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:12:01 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/16 11:16:06 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	cwd 4096 because it is the max path len
int	ft_pwd(char **args)
{
	char	cwd[4096];

	if (arg_count(args) != 1)
		return (printf("pwd: too many arguments\n"), 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd hatası");
	return (0);
}
