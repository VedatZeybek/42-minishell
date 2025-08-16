/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:50:48 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/16 21:58:48 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exist(t_list **env, char *cont)
{
	while (*env)
	{
		if (ft_strncmp((*env)->content, cont, ft_strlen(cont)) == 0)
		{
			free((*env)->content);
			(*env)->content = ft_strdup(cont);
			return (1);
		}
		else
			env = &(*env)->next;
	}
	return (0);
}

int	ft_export(t_list **env, char *cont)
{
	int	i;

	if (ft_isdigit(cont[0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", cont);
		return (0);
	}
	if (ft_strrchr(cont, '=') == NULL || !cont)
		return (0);
	i = 0;
	while (cont[i])
	{
		if (cont[i] == '=')
			break ;
		if (!ft_isalnum(cont[i]) && cont[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", cont);
			return (0);
		}
		i++;
	}
	if (!is_exist(env, cont))
		ft_lstadd_back(env, ft_lstnew(ft_strdup(cont)));
	return (0);
}
