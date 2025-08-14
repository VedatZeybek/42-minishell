/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:04 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/14 15:24:14 by vzeybek          ###   ########.fr       */
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
void print_commands(t_command *command)
{
	t_command *tmp = command;

	while (tmp)
	{
		printf("command args: ");
		int i = 0;
		while (tmp->argv[i])
		{
			printf("%s ", tmp->argv[i]);
			i++;
		}

		t_redir *redir = tmp->redirections;
		while (redir)
		{
			printf("[redirection type: %d], file name: %s",
				redir->type, redir->filename);
			redir = redir->next;
		}
        printf("\n");
        tmp = tmp->next;
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
		//print_tokens(tokens);
		t_command *command = parse_command(&tokens);
		print_commands(command);
	}
	return (0);
}
