/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:46:11 by epakdama          #+#    #+#             */
/*   Updated: 2025/08/15 11:58:31 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int	arg_count(char **args);
int	ft_cd(char **args);
int	ft_pwd(char **args);
int	ft_echo(char **args);
int	ft_env(char **argv, char **envp);
int ft_exit(char **args);
int	ft_exit_child(char **args);

#endif