/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vedat.zeybek@student.42.fr    	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:53:12 by vzeybek      	   #+#    #+#             */
/*   Updated: 2025/11/03 22:53:16 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_handle_heredoc_redir(t_redir *redir, int *last_heredoc_rd);
static int	ft_handle_other_redir(t_redir *redir, int *last_heredoc_rd);
static int	ft_apply_last_heredoc(int last_heredoc_rd);

int	ft_handle_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		last_heredoc_rd;
	int		ret;

	if (!cmd || !cmd->redirections)
		return (0);
	last_heredoc_rd = -1;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
			ret = ft_handle_heredoc_redir(redir, &last_heredoc_rd);
		else
			ret = ft_handle_other_redir(redir, &last_heredoc_rd);
		if (ret != 0)
			return (ret);
		redir = redir->next;
	}
	return (ft_apply_last_heredoc(last_heredoc_rd));
}

static int	ft_handle_heredoc_redir(t_redir *redir, int *last_heredoc_rd)
{
	int	pipefd[2];
	int	ret;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		if (*last_heredoc_rd != -1)
			close(*last_heredoc_rd);
		return (1);
	}
	ret = ft_write_heredoc_to_fd(redir->filename, pipefd[1]);
	close(pipefd[1]);
	if (ret != 0)
	{
		close(pipefd[0]);
		if (*last_heredoc_rd != -1)
			close(*last_heredoc_rd);
		return (ret);
	}
	if (*last_heredoc_rd != -1)
		close(*last_heredoc_rd);
	*last_heredoc_rd = pipefd[0];
	return (0);
}

static int	ft_handle_other_redir(t_redir *redir, int *last_heredoc_rd)
{
	int	ret;

	ret = ft_process_redirection(redir);
	if (ret != 0)
	{
		if (*last_heredoc_rd != -1)
			close(*last_heredoc_rd);
		return (ret);
	}
	if (redir->type == TOKEN_REDIRECT_IN && *last_heredoc_rd != -1)
	{
		close(*last_heredoc_rd);
		*last_heredoc_rd = -1;
	}
	return (0);
}

static int	ft_apply_last_heredoc(int last_heredoc_rd)
{
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
