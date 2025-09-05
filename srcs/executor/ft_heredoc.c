#include "ft_executor.h"
#include "get_next_line.h"

int ft_open_heredoc(char *limiter)
{
    int fd[2];
    pid_t pid;
    int status;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (1);
    }

    pid = fork();
    if (pid == -1)
        return (perror("fork"), 1);

    if (pid == 0)
    {
        close(fd[0]);
        char *line;
        while (1)
        {
            write(STDOUT_FILENO, "> ", 2);
            line = get_next_line(STDIN_FILENO);
            if (!line)
                exit(0);

            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n')
                line[len - 1] = '\0';

            if (strcmp(line, limiter) == 0)
            {
                free(line);
                exit(0);
            }
            write(fd[1], line, strlen(line));
            write(fd[1], "\n", 1);
            free(line);
        }
    }
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    waitpid(pid, &status, 0);
    return 0;
}
