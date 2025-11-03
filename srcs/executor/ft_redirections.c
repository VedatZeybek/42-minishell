/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:37:30 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/03 16:44:53 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_write_heredoc_to_fd(char *limiter, int wfd);

int	ft_handle_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		last_heredoc_rd;
	int		pipefd[2];
	int		ret;

	if (!cmd || !cmd->redirections)
		return (0);
	last_heredoc_rd = -1;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				if (last_heredoc_rd != -1)
					close(last_heredoc_rd);
				return (1);
			}
			ret = ft_write_heredoc_to_fd(redir->filename, pipefd[1]);
			close(pipefd[1]);
			if (ret != 0)
			{
				close(pipefd[0]);
				if (last_heredoc_rd != -1)
					close(last_heredoc_rd);
				return (ret);
			}
			if (last_heredoc_rd != -1)
				close(last_heredoc_rd);
			last_heredoc_rd = pipefd[0];
		}
		else
		{
			ret = ft_process_redirection(redir);
			if (ret != 0)
			{
				if (last_heredoc_rd != -1)
					close(last_heredoc_rd);
				return (ret);
			}
			if (redir->type == TOKEN_REDIRECT_IN && last_heredoc_rd != -1)
			{
				close(last_heredoc_rd);
				last_heredoc_rd = -1;
			}
		}
		redir = redir->next;
	}
	if (last_heredoc_rd != -1)
	{
		if (dup2(last_heredoc_rd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(last_heredoc_rd);
			return (1);
		}
		close(last_heredoc_rd);
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
