/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:04 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/16 09:03:36 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void print_tokens(t_token *tokens)
{
	t_token *tmp = tokens;
	while (tmp)
	{
		printf("Token: '%s', Type: %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
}

void	print_command(t_command *cmd)
{
	int	i;
	t_redir	*redir;

	while (cmd)
	{
		printf("=== COMMAND ===\n");
		i = 0;
		while (cmd->args && cmd->args[i].value)
		{
			printf("  argv[%d] = \"%s\" (type = %d)\n",
				i, cmd->args[i].value, cmd->args[i].type);
			i++;
		}
		redir = cmd->redirections;
		while (redir)
		{
			printf("  redir: type = %d, filename = \"%s\"\n",
				redir->type, redir->filename);
			redir = redir->next;
		}
		if (cmd->next)
			printf("  |\n  v\n");
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	shell.running = 1;
	while (shell.running)
	{
		line = read_line();
		if (!line)
			break ;
		execute_command(line, env);
		char *input = line;
		t_token *tokens = tokenize(input);
		print_tokens(tokens);
		t_command *command = parse_command(&tokens);
		print_command(command);
	}
	return (0);
}
