/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:22:03 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/04 10:27:25 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i].value)
		{
			if (cmd->argv[i].value)
				free(cmd->argv[i].value);
			i++;
		}
		free(cmd->argv);
	}
	if (cmd->redirections)
		free_redirs(cmd->redirections);
	free(cmd);
}

void	free_command_list(t_command *cmd)
{
	t_command	*tmp;
	t_command	*next;

	tmp = cmd;
	while (tmp)
	{
		next = tmp->next;
		free_command(tmp);
		tmp = next;
	}
}
