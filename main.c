/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:04 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 12:18:06 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_status = 0;

static void	run_input(char *line, t_vars *vars)
{
	t_token		*tokens;
	t_command	*command;

	tokens = tokenize(line);
	if (syntax_check(tokens))
	{
		free_tokens(tokens);
		return ;
	}
	command = parse_command(&tokens);
	free_tokens(tokens);
	if (command)
	{
		ft_run_commands(command, vars);
		free_command_list(command);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell		shell;
	t_vars		vars;
	char		*line;

	(void)argc;
	(void)argv;
	shell.running = 1;
	ft_init_vars(&vars, env);
	while (shell.running)
	{
		line = read_line();
		if (!line)
			break ;
		run_input(line, &vars);
		free(line);
	}
	ft_free_vars(&vars);
	return (0);
}

//tab sinyali ayarlanabilir
//yeni path directory export edince ordaki komut çalışmıyor
//heredoc hatalı 
//builtins pipe ile verilince leak var

