/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:21:56 by epakdama          #+#    #+#             */
/*   Updated: 2025/10/25 14:21:56 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	count_args(t_arg *args);
static void	copy_args(t_arg *new_args, t_arg *old_args, int count);

int	add_arg(t_arg **args, char *value, t_token_type type)
{
	t_arg	*new_args;
	int		i;

	if (!value || !args)
		return (0);
	i = count_args(*args);
	new_args = malloc((i + 2) * sizeof(t_arg));
	if (!new_args)
		return (0);
	copy_args(new_args, *args, i);
	if (*args)
		free(*args);
	new_args[i].value = ft_strdup(value);
	new_args[i].type = type;
	new_args[i + 1].value = NULL;
	new_args[i + 1].type = 0;
	*args = new_args;
	return (1);
}

static int	count_args(t_arg *args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i].value)
			i++;
	}
	return (i);
}

static void	copy_args(t_arg *new_args, t_arg *old_args, int count)
{
	int	j;

	j = 0;
	if (old_args)
	{
		while (j < count)
		{
			new_args[j] = old_args[j];
			j++;
		}
	}
}
