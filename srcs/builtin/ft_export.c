/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:50:48 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/16 11:01:23 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_list **env, char *content)
{
	ft_lstadd_back(env, ft_lstnew(ft_strdup(content)));
	return (0);
}
