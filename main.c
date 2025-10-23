/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:04 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 17:59:03 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "./includes/ft_executor.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_shell		shell;
	t_vars		vars;
	t_token		*tokens;
	t_command	*command;
	char		*line;
	char		*input;

	(void)	argc;
	(void)	argv;
	shell.running = 1;
	ft_init_vars(&vars, env);
	while (shell.running)
	{
		line = read_line();
		if (!line)
			break ;
		input = line;
		tokens = tokenize(input);
		command = parse_command(&tokens);
		if (command)
		{
			ft_run_commands(command, &vars);
			free_command(command);
		}
		free_tokens(tokens);
		free(line);
	}
	ft_free_vars(&vars);
	return (0);
}
