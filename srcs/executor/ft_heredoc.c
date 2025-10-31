/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:22:35 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 13:56:10 by vedat-zeybe      ###   ########.fr       */
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

static int	handle_heredoc_error(char *limiter)
{
	if (!limiter || !*limiter)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `newline'\n", 2);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

static void	write_line_to_pipe(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	if (ft_strlen(line) == 0 || line[ft_strlen(line) - 1] != '\n')
		write(fd, "\n", 1);
}

static int	read_heredoc_lines(int *fd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (check_limiter(line, limiter))
		{
			free(line);
			break ;
		}
		write_line_to_pipe(fd[1], line);
		free(line);
	}
	return (0);
}

int	ft_open_heredoc(char *limiter)
{
	int		fd[2];

	if (handle_heredoc_error(limiter))
		return (1);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	read_heredoc_lines(fd, limiter);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd[0]);
		return (1);
	}
	close(fd[0]);
	return (0);
}
