/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:22:46 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/13 19:11:35 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	execute_command(char *line, char **envp)
{
	char	**argv;
	char	*cmd_path;
	pid_t	pid;
	int		status;

	if (!line || !*line)
		return ;
	argv = ft_split(line, ' ');
	if (!argv || !argv[0])
		return ;
	pid = fork();
	if (pid == 0)
	{
		cmd_path = get_cmd_path(argv[0], envp);
		if (!cmd_path)
		{
			fprintf(stderr, "minishell: command not found: %s\n", argv[0]);
			exit(127);
		}
		execve(cmd_path, argv, envp);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
		perror("fork");
	free_splitted(argv);
}
