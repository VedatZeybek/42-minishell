/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:37:30 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/07 17:14:29 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_executor.h"
#include <sys/stat.h>


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
	if (vars->path)
		return (ft_check_path(vars, cmd_name));
	
	return (NULL);
}

int	ft_run_external_cmd(t_command *cmd, t_vars *vars)
{
	char		*cmd_path;
	char		**str;
	struct stat	st;

	str = copy_argv_to_string_array(cmd, argv_length(cmd));
	if (!cmd || !cmd->argv || !cmd->argv[0].value || cmd->argv[0].value[0] == '\0')
	{
		g_exit_status = 0;
		return (0);
	}

	// Önce stat ile kontrol et (ama sadece path içeriyorsa kullan)
	int stat_result = stat(cmd->argv[0].value, &st);
	
	// Eğer path içeriyorsa (./ veya / ile başlıyorsa veya / içeriyorsa)
	if (ft_strchr(cmd->argv[0].value, '/'))
	{
		// Dosya/dizin mevcut değilse
		if (stat_result == -1)
		{
			g_exit_status = 127;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd->argv[0].value, ft_strlen(cmd->argv[0].value));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
			return (127);
		}
		
		// Dizinse
		if (S_ISDIR(st.st_mode))
		{
			g_exit_status = 126;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd->argv[0].value, ft_strlen(cmd->argv[0].value));
			write(STDERR_FILENO, ": Is a directory\n", 17);
			return (126);
		}
		
		// Execute yetkisi yoksa
		if (access(cmd->argv[0].value, X_OK) == -1)
		{
			g_exit_status = 126;
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd->argv[0].value, ft_strlen(cmd->argv[0].value));
			write(STDERR_FILENO, ": Permission denied\n", 20);
			return (126);
		}
		
		// Dosya var ve çalıştırılabilir, direkt execve çağır
		if (execve(cmd->argv[0].value, str, vars->envp) == -1)
		{
			perror("minishell");
			g_exit_status = 1;
			return (1);
		}
	}
	
	// Path içermiyorsa, PATH'te ara
	// NOT: Mevcut dizinde dosya/dizin olsa bile PATH'te ara
	cmd_path = ft_find_cmd_path(cmd->argv[0].value, vars->envp, vars);
	
	if (!cmd_path)
	{
		// PATH'te bulunamadı, command not found
		g_exit_status = 127;
		write(STDERR_FILENO, cmd->argv[0].value, ft_strlen(cmd->argv[0].value));
		write(STDERR_FILENO, ": command not found\n", 20);
		return (127);
	}

	// PATH'te bulundu, çalıştır
	if (execve(cmd_path, str, vars->envp) == -1)
	{
		perror("minishell");
		free(cmd_path);
		g_exit_status = 1;
		return (1);
	}
	
	free(cmd_path);
	return (0);
}