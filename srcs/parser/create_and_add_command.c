/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_and_add_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:22:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/25 14:22:01 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_command	*create_command(t_arg *args, t_redir *redirections)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = args;
	cmd->redirections = redirections;
	cmd->next = NULL;
	return (cmd);
}

void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*current;

	if (!head || !new_cmd)
		return ;
	if (!*head)
	{
		*head = new_cmd;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}
