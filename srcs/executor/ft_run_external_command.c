#include "../../includes/ft_executor.h"
#include <sys/stat.h>

static void	write_error(char *prefix, char *cmd, char *suffix)
{
	if (prefix)
		write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, suffix, ft_strlen(suffix));
}

static int	execute_with_path(char *cmd_name, char **str, char **envp)
{
	struct stat	st;

	if (stat(cmd_name, &st) == -1)
	{
		g_exit_status = 127;
		write_error("minishell: ", cmd_name, ": No such file or directory\n");
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		g_exit_status = 126;
		write_error("minishell: ", cmd_name, ": Is a directory\n");
		return (126);
	}
	if (access(cmd_name, X_OK) == -1)
	{
		g_exit_status = 126;
		write_error("minishell: ", cmd_name, ": Permission denied\n");
		return (126);
	}
	if (execve(cmd_name, str, envp) == -1)
		perror("minishell");
	g_exit_status = 1;
	return (1);
}

static int	execute_from_env_path(char *cmd_name, t_vars *vars, char **str)
{
	char	*cmd_path;

	cmd_path = ft_find_cmd_path(cmd_name, vars->envp, vars);
	if (!cmd_path)
	{
		g_exit_status = 127;
		write_error(NULL, cmd_name, ": command not found\n");
		return (127);
	}
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

int	ft_run_external_cmd(t_command *cmd, t_vars *vars)
{
	char	**str;

	str = copy_argv_to_string_array(cmd, argv_length(cmd));
	if (!cmd || !cmd->argv || !cmd->argv[0].value \
		|| cmd->argv[0].value[0] == '\0')
	{
		g_exit_status = 0;
		return (0);
	}
	if (ft_strchr(cmd->argv[0].value, '/'))
		return (execute_with_path(cmd->argv[0].value, str, vars->envp));
	return (execute_from_env_path(cmd->argv[0].value, vars, str));
}