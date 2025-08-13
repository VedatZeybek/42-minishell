/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:15:48 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/03 19:06:27 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest_u;
	char	*src_u;

	dest_u = (char *)(dst);
	src_u = (char *)(src);
	if (len == 0 || dest_u == src_u)
		return (dst);
	i = len;
	if (dest_u > src_u)
	{
		while (i > 0)
		{
			dest_u[i - 1] = src_u[i - 1];
			i--;
		}
		return (dst);
	}
	else
	{
		ft_memcpy(dest_u, src_u, len);
	}
	return (dst);
}
