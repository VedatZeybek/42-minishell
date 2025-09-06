/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:37:30 by epakdama          #+#    #+#             */
/*   Updated: 2025/09/03 15:11:53 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"

int	ft_is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_check_builtin(cmd_name, "echo") || ft_check_builtin(cmd_name, "cd"))
		return (1);
	if (ft_check_builtin(cmd_name, "pwd")
		|| ft_check_builtin(cmd_name, "export"))
		return (1);
	if (ft_check_builtin(cmd_name, "unset")
		|| ft_check_builtin(cmd_name, "env"))
		return (1);
	if (ft_check_builtin(cmd_name, "exit"))
		return (1);
	return (0);
}

int	ft_call_builtin(t_command *cmd, t_vars *vars)
{
	char	**str;

	str = copy_argv_to_string_array(cmd, argv_length(cmd));
	if (ft_check_builtin(cmd->argv[0].value, "echo"))
		return (ft_echo(str));
	else if (ft_check_builtin(cmd->argv[0].value, "cd"))
		return (ft_cd(str));
	else if (ft_check_builtin(cmd->argv[0].value, "pwd"))
		return (ft_pwd(str));
	else if (ft_check_builtin(cmd->argv[0].value, "env"))
		return (ft_env(str, vars->envp));
    else if (ft_check_builtin(cmd->argv[0].value, "exit"))
		return (ft_exit_child(str));
	else if (ft_check_builtin(cmd->argv[0].value, "export"))
		return (ft_export(vars, str));
	else if (ft_check_builtin(cmd->argv[0].value, "unset"))
		return (ft_unset(vars, str));
	free_splitted(str);
	return (0);
}

int	ft_run_builtin(t_command *cmd, t_vars *vars)
{
	if (!cmd || !cmd->argv || !cmd->argv)
		return (1);
	return (ft_call_builtin(cmd, vars));
}

char	*ft_find_cmd_path(char *cmd_name, char **envp, t_vars *vars)
{
	if (!cmd_name || !envp || !vars)
		return (NULL);
	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	if (vars->path)
		return (ft_check_path(vars, cmd_name));
	return (NULL);
}

int	ft_run_external_cmd(t_command *cmd, t_vars *vars)
{
	char	*cmd_path;
	char	**str;

	str = copy_argv_to_string_array(cmd, argv_length(cmd));
	if (!cmd || !cmd->argv || !cmd->argv)
		return (1);
	cmd_path = ft_find_cmd_path(cmd->argv[0].value, vars->envp, vars);
	if (!cmd_path)
	{
		printf("minishell: '%s': command not found\n", cmd->argv->value);
		return (127);
	}
	if (execve(cmd_path, str, vars->envp) == -1)
	{
		printf("minishell: '%s': command not found\n", cmd->argv->value);
		free(cmd_path);
		return (1);
	}
	free(cmd_path);
	return (0);
}
