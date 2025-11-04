/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:22:35 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/04 10:28:47 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_limiter(char *line, char *limiter)
{
	size_t	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& ft_strlen(line) == ft_strlen(limiter))
		return (1);
	return (0);
}

static void	write_line_to_fd(int fd, char *line)
{
	if (line && *line)
		write(fd, line, ft_strlen(line));
	if (!line || ft_strlen(line) == 0 || line[ft_strlen(line) - 1] != '\n')
		write(fd, "\n", 1);
}

int	ft_write_heredoc_to_fd(char *limiter, int wfd)
{
	char	*line;

	if (!limiter || !*limiter)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `newline'\n", 2);
		g_exit_status = 2;
		return (1);
	}
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (check_limiter(line, limiter))
		{
			free(line);
			break ;
		}
		write_line_to_fd(wfd, line);
		free(line);
	}
	return (0);
}

static int	ft_create_heredoc_pipe(char *limiter, int *pipe_fd)
{
	if (!limiter || !*limiter)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `newline'\n", 2);
		g_exit_status = 2;
		return (1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	if (ft_write_heredoc_to_fd(limiter, pipe_fd[1]) != 0)
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return (1);
	}
	close(pipe_fd[1]);
	return (0);
}

int	ft_open_heredoc(char *limiter)
{
	int	fd[2];

	if (ft_create_heredoc_pipe(limiter, fd) != 0)
		return (1);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd[0]);
		return (1);
	}
	close(fd[0]);
	return (0);
}
