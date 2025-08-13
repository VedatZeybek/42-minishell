/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:12:25 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/12 15:06:12 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strrchr(const char *str, char c)
{
	char	*last_char;

	last_char = NULL;
	while (*str)
	{
		if (*str == c)
			last_char = (char *)str;
		str++;
	}
	if (last_char)
		return (last_char);
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}
