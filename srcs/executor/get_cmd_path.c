/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:22:50 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/13 19:11:39 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path_dir(char **envp)
{
	int		i;
	char	*path;
	char	**result;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	result = ft_split(path, ':');
	if (!result)
	{
		free(result);
		error(ERR_PATH);
	}
	return (result);
}

static char	*find_cmd_in_path(char *cmd, char **dirs)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			error(ERR_PATH);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			error(ERR_PATH);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**path_dir;
	char	*full_path;

	path_dir = get_path_dir(envp);
	if (!path_dir)
		error(ERR_CMD);
	full_path = find_cmd_in_path(cmd, path_dir);
	free_splitted(path_dir);
	return (full_path);
}
