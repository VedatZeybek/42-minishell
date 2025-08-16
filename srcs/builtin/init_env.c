/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 09:50:07 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/16 10:19:10 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_env(char **envp)
{
	t_list	*env;
	int		i;

	if (envp[0])
		env = ft_lstnew(ft_strdup(envp[0]));
	else
		return (NULL);
	i = 1;
	while (envp[i])
		ft_lstadd_back(&env, ft_lstnew(ft_strdup(envp[i++])));
	return (env);
}
