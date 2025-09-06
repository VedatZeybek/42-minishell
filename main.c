/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:04 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 15:07:04 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "./includes/ft_executor.h"

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
		while (cmd->argv && cmd->argv[i].value)
		{
			printf("  argv[%d] = \"%s\" (type = %d)\n",
				i, cmd->argv[i].value, cmd->argv[i].type);
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
	t_vars	vars;

	(void)argc;
	(void)argv;
	(void)env;
	shell.running = 1;
	ft_init_vars(&vars, env);
	while (shell.running)
	{
		line = read_line();
		if (!line)
			break ;
		char *input = line;
		t_token *tokens = tokenize(input);
		//print_tokens(tokens);
		t_command *command = parse_command(&tokens);
		//print_command(command);
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
