/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:15:37 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/03 23:29:26 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	i = 0;
	if (num == 0)
		return (dst);
	if (dst == NULL && src == NULL)
		return (NULL);
	temp1 = (unsigned char *) dst;
	temp2 = (unsigned char *) src;
	while (i < num)
	{
		temp1[i] = temp2[i];
		i++;
	}
	return (dst);
}
