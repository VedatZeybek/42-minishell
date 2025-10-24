#include "ft_executor.h"
#include "get_next_line.h"

static int	set_pipe_and_fork(int fd[2], pid_t *pid);
static void	heredoc_child(int write_fd, char *limiter);

int	ft_open_heredoc(char *limiter)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (set_pipe_and_fork(fd, &pid) != 0)
		return (1);
	if (pid == 0)
		heredoc_child(fd[1], limiter);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (0);
}

static int	check_limiter(char *line, char *limiter)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& ft_strlen(line) == ft_strlen(limiter))
		return (1);
	return (0);
}

static void	heredoc_child(int write_fd, char *limiter)
{
	char	*line;

	close(write_fd);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(0);
		if (check_limiter(line, limiter))
		{
			free(line);
			exit(0);
		}
		write(write_fd, line, ft_strlen(line));
		if (line[ft_strlen(line) - 1] != '\n')
			write(write_fd, "\n", 1);
		free(line);
	}
}

static int	set_pipe_and_fork(int fd[2], pid_t *pid)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		return (1);
	}
	return (0);
}
