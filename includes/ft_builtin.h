/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vedat-zeybek <vedat-zeybek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:46:11 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/24 18:17:25 by vedat-zeybe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		ft_arg_count(char **args);
int		ft_cd(char **args);
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