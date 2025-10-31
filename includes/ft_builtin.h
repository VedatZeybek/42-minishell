/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:46:11 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/31 12:00:06 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

# include "minishell.h"

int		ft_arg_count(char **args);
int		ft_cd(char **args, t_vars *vars);
int		ft_pwd(char **args);
int		ft_echo(char **args);
int		ft_env(char **argv, char **envp);
int		ft_exit(char **args);
int		ft_exit_child(char **args);
int		ft_env_len(char **envp);
int		ft_is_valid_input(char *str);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	**ft_realloc_add(char **arr, char *new_str);

#endif