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

void print_command(t_command *cmd)
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
		char *input = line;
		t_token *tokens = tokenize(input);
		print_tokens(tokens);
		t_command *command = parse_command(&tokens);
		print_command(command);
		if (command)
		{
			ft_run_commands(command, env);
			free_command(command);
		}
		free_tokens(tokens);
		free(line);
	}
	return (0);
}
