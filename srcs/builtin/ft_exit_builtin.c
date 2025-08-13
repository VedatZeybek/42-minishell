/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:47:09 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/13 21:48:38 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_builtin(char *msg)
{
	if (!msg)
		exit(EXIT_SUCCESS);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
