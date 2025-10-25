/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:37:30 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/25 14:29:38 by epakdama         ###   ########.fr       */
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
	int		result;

	str = copy_argv_to_string_array(cmd, argv_length(cmd));
	result = 0;
	if (ft_check_builtin(cmd->argv[0].value, "echo"))
		result = ft_echo(str);
	else if (ft_check_builtin(cmd->argv[0].value, "cd"))
		result = ft_cd(str);
	else if (ft_check_builtin(cmd->argv[0].value, "pwd"))
		result = ft_pwd(str);
	else if (ft_check_builtin(cmd->argv[0].value, "env"))
		result = ft_env(str, vars->envp);
	else if (ft_check_builtin(cmd->argv[0].value, "exit"))
		result = ft_exit_child(str);
	else if (ft_check_builtin(cmd->argv[0].value, "export"))
		result = ft_export(vars, str);
	else if (ft_check_builtin(cmd->argv[0].value, "unset"))
		result = ft_unset(vars, str);
	free_splitted(str);
	return (result);
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
	if (vars->path)
		return (ft_check_path(vars, cmd_name));
	return (NULL);
}
