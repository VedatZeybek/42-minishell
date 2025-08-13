/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:15:04 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/02 18:47:34 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *ptr, int value, size_t n)
{
	size_t			i;
	unsigned char	*buffer;

	buffer = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		if (buffer[i] == (unsigned char)value)
			return ((void *)(buffer + i));
		i++;
	}
	return (NULL);
}
