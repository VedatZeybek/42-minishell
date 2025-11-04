/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:37:30 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/04 10:28:43 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	return (0);
}

int	ft_open_input_file(char *filename, int flags)
{
	int	fd;

	if (!filename || !*filename)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `newline'\n", 2);
		g_exit_status = 2;
		return (1);
	}
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		g_exit_status = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_open_output_file(char *filename, int flags)
{
	int	fd;

	if (!filename || !*filename)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `newline'\n", 2);
		g_exit_status = 2;
		return (1);
	}
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
