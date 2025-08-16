/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:46:11 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/16 11:13:04 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		arg_count(char **args);
int		ft_cd(char **args);
int		ft_pwd(char **args);
int		ft_echo(char **args);
int		ft_env(char **argv, t_list *env);
int		ft_unset(t_list **env, char *content);
int		ft_export(t_list **env, char *content);
t_list	*init_env(char **envp);

#endif