/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:37:30 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 15:04:07 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

int	ft_handle_redirections(t_command *cmd)
{
	t_redir	*redir;

	if (!cmd || !cmd->redirections)
		return (0);
	redir = cmd->redirections;
	while (redir)
	{
		if (ft_process_redirection(redir) != 0)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	ft_process_redirection(t_redir *redir)
{
	int	flags;

	if (!redir)
		return (0);
	if (redir->type == TOKEN_REDIRECT_IN)
		return (ft_open_input_file(redir->filename, O_RDONLY));
	else if (redir->type == TOKEN_REDIRECT_OUT)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		return (ft_open_output_file(redir->filename, flags));
	}
	else if (redir->type == TOKEN_APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		return (ft_open_output_file(redir->filename, flags));
	}
	else if (redir->type == TOKEN_HEREDOC)
	{
    	return (ft_open_heredoc(redir->filename));
	}
	return (0);
}

int	ft_open_input_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_open_output_file(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
