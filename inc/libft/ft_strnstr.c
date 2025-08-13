/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:12:23 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/03 14:00:11 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	if (ft_strlen(needle) > ft_strlen(haystack) || ft_strlen(needle) > len)
		return (NULL);
	while (haystack[i] && needle[j] && (i + j < len))
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] && (i + j < len))
		{
			if (j == ft_strlen(needle) - 1)
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
