/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:04 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/13 18:23:04 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int ac, char **argv, char **env)
{
	t_shell	shell;
	char	*line;

	shell.running = 1;
	while (shell.running)
	{
		line = read_line();
		if (!line)
			break ;
		execute_command(line, env);
		free(line);
	}
	return (0);
}
