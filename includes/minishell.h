/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:22:57 by epakdama          #+#    #+#             */
/*   Updated: 2025/11/03 15:21:46 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define BLUE "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN "\001\033[0;36m\002"
# define LIGHT_RED "\001\033[91m\002"
# define LIGHT_GREEN "\001\033[92m\002"
# define LIGHT_YELLOW "\001\033[93m\002"
# define LIGHT_BLUE "\001\033[94m\002"
# define LIGHT_MAGENTA "\001\033[95m\002"
# define LIGHT_CYAN "\001\033[96m\002"
# define RESET "\001\033[0m\002"

# define ERR_INPUT "Invalid number of arguments."
# define ERR_FILE "Invalid File."
# define ERR_PATH "Path Not Found."
# define ERR_CMD "Command Not Found."
# define ERR_PRC "Process Failed."
# define ERR_PIPE "Pipe Creation Failed."
# define ERR_EXCVE "Execution Failed."
# define ERR_CLS "Close File Failed."

extern int				g_exit_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_WHITESPACE,
	TOKEN_INVALID
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_shell
{
	int					running;
}						t_shell;

typedef struct s_args
{
	t_token_type		type;
	char				*value;
}						t_arg;

typedef struct s_redir
{
	t_token_type		type;
	char				*filename;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	t_arg				*argv;
	t_redir				*redirections;
	struct s_command	*next;
}						t_command;

typedef struct s_vars
{
	char				**envp;
	char				**path;
}						t_vars;

typedef struct s_pipes
{
	int					prev[2];
	int					curr[2];
}						t_pipes;

char					*read_line(void);
void					free_splitted(char **str);
int						syntax_error(const char *near);
int						is_redir(int type);
const char				*token_repr(int type);

// Executor
int						ft_run_commands(t_command *cmd_list, t_vars *vars);
void					ft_exec_single(t_command *cmd, t_vars *vars);
void					ft_exec_pipe(t_command *cmd_list, t_vars *vars);
char					*ft_check_path(t_vars *vars, char *cmd);
int						ft_count_cmds(t_command *cmd_list);
void					ft_init_vars(t_vars *vars, char **envp);
int						ft_check_builtin(const char *c, const char *b);
int						ft_call_builtin(t_command *cmd, t_vars *vars);
int						ft_run_builtin(t_command *cmd, t_vars *vars);
int						ft_run_external_cmd(t_command *cmd, t_vars *vars);
char					*ft_find_cmd_path(char *cmd_name, char **envp,
							t_vars *vars);
int						ft_handle_redirections(t_command *cmd);
int						ft_process_redirection(t_redir *redir);
int						ft_open_input_file(char *filename, int flags);
int						ft_open_output_file(char *filename, int flags);
int						ft_is_builtin(char *cmd_name);
void					wait_all_children(int count);

char					**copy_argv_to_string_array(t_command *cmd,
							size_t argv_len);
void					free_string_array(char **arr);
size_t					argv_length(t_command *cmd);
int						ft_export(t_vars *vars, char **args);
int						ft_unset(t_vars *vars, char **args);
int						ft_open_heredoc(char *limiter);
void					ft_free_vars(t_vars *vars);
void					exec_child_process(t_command *cmd,
							t_command *cmd_list_head, t_vars *vars,
							t_pipes *pipes);
const char				*ft_get_env_elem(char **envp, char *elem_name);

// Builtin
int						ft_arg_count(char **args);
int						ft_cd(char **args, t_vars *vars);
int						ft_pwd(char **args);
int						ft_echo(char **args);
int						ft_env(char **argv, char **envp);
int						ft_exit(char **args, t_vars *vars, t_command *cmd_list);
int						ft_exit_child(char **args);
int						ft_env_len(char **envp);
int						ft_is_valid_input(char *str);
char					*ft_strjoin3(char *s1, char *s2, char *s3);
char					**ft_realloc_add(char **arr, char *new_str);
int						is_all_number(char *str);
int						ft_error_msg(char *arg);
int						export_valid_checks(char *key, char *eq, char *args);
int						print_exports(t_vars *vars);
int						ft_is_valid_key(char *key);

// Parser
int						add_arg(t_arg **args, char *value, t_token_type type);
void					free_command(t_command *cmd);
void					add_command(t_command **head, t_command *new_cmd);
void					free_command_list(t_command *cmd);
t_command				*create_command(t_arg *args, t_redir *redirections);
t_command				*parse_command(t_token **tokens);

// Tokenizer
t_token					*tokenize(char *input);
t_token					*create_token(char *value, t_token_type type);
void					token_redirect(char *input, t_token **token, int *i);
void					add_token(t_token **head, t_token *new_token);
int						is_whitespace(char c);
void					free_tokens(t_token *token);
char					*ft_strjoin_free(char *s1, char *s2);
int						handle_word(char *input, t_token **token, int *i);
int						syntax_check(t_token *tok);

#endif
