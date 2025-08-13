/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:16:00 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/11 12:54:36 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buffer, int value, size_t num)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = buffer;
	while (i < num)
	{
		*ptr = (unsigned char) value;
		i++;
		ptr++;
	}
	return (buffer);
}
