/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:23:04 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/13 19:14:49 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

//ben vedat nasıl yazdım bunu bilmiyorum ama
//bunu yazdım ve çalışıyor.
// bu kodu yazdım ve çalışıyor.


void print_tokens(t_token *tokens)
{
    t_token *tmp = tokens;
    while (tmp)
    {
        printf("Token: '%s', Type: %d\n", tmp->value, tmp->type);
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
		print_tokens(tokens);
		free(line);
	}
	return (0);
}
