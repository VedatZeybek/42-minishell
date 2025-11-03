/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:04 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/03 18:12:05 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			g_exit_status = 0;

static int	check_unclosed_quotes(const char *s)
{
	int		i;
	char	open;

	if (!s)
		return (0);
	i = 0;
	open = 0;
	while (s[i])
	{
		if (!open && (s[i] == '\'' || s[i] == '\"'))
			open = s[i];
		else if (open && s[i] == open)
			open = 0;
		i++;
	}
	if (open)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
			2);
		ft_putchar_fd(open, 2);
		ft_putstr_fd("'\n", 2);
		g_exit_status = 2;
		return (1);
	}
	return (0);
}

static void	run_input(char *line, t_vars *vars)
{
	t_token		*tokens;
	t_command	*command;

	if (check_unclosed_quotes(line))
		return ;
	tokens = tokenize(line, vars);
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
	t_shell	shell;
	t_vars	vars;
	char	*line;

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
	return (g_exit_status);
}
