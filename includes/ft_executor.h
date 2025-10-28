/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/28 17:43:01 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXECUTOR_H
# define FT_EXECUTOR_H

# include "minishell.h"

typedef struct s_vars
{
	char	**envp;
	char	**path;
}			t_vars;

typedef struct s_pipes
{
	int		prev[2];
	int		curr[2];
}	t_pipes;

int			ft_run_commands(t_command *cmd_list, t_vars *vars);
void		ft_exec_single(t_command *cmd, t_vars *vars);
void		ft_exec_pipe(t_command *cmd_list, t_vars *vars);
char		*ft_check_path(t_vars *vars, char *cmd);
int			ft_count_cmds(t_command *cmd_list);
void		ft_init_vars(t_vars *vars, char **envp);
int			ft_check_builtin(const char *c, const char *b);
int			ft_call_builtin(t_command *cmd, t_vars *vars);
int			ft_run_builtin(t_command *cmd, t_vars *vars);
int			ft_run_external_cmd(t_command *cmd, t_vars *vars);
char		*ft_find_cmd_path(char *cmd_name, char **envp, t_vars *vars);
int			ft_handle_redirections(t_command *cmd);
int			ft_process_redirection(t_redir *redir);
int			ft_open_input_file(char *filename, int flags);
int			ft_open_output_file(char *filename, int flags);
int			ft_is_builtin(char *cmd_name);
void		wait_all_children(int count);

// my_additions
char		**copy_argv_to_string_array(t_command *cmd, size_t argv_len);
void		free_string_array(char **arr);
size_t		argv_length(t_command *cmd);
int			ft_export(t_vars *vars, char **args);
int			ft_unset(t_vars *vars, char **args);
int			ft_open_heredoc(char *limiter);
void		ft_free_vars(t_vars *vars);
void		exec_child_process(t_command *cmd, t_command *cmd_list_head,
				t_vars *vars, t_pipes *pipes);

#endif
