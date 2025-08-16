/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:51:51 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/16 11:07:11 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_list **env, char *content)
{
	while (*env)
	{
		if (ft_strncmp((*env)->content, content, ft_strlen(content)) == 0)
		{
			free((*env)->content);
			*env = (*env)->next;
		}
		else
			env = &(*env)->next;
	}
	return (0);
}
