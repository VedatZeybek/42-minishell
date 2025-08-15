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

<<<<<<< HEAD
void print_commands(t_command *command)
=======

void print_command(t_command *cmd)
>>>>>>> main
{
    int i;
    while (cmd)
    {
        printf("Command:\n");
        for (i = 0; cmd->argv && cmd->argv[i]; i++)
            printf("  argv[%d] = %s\n", i, cmd->argv[i]);
        t_redir *r = cmd->redirections;
        while (r)
        {
            printf("  redir type=%d target=%s\n", r->type, r->filename);
            r = r->next;
        }
        cmd = cmd->next;
        if (cmd)
            printf("---- PIPE ----\n");
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
