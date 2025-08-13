/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:12:21 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/11 10:00:46 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1unsigned;
	unsigned char	*s2unsigned;
	size_t			i;

	s1unsigned = (unsigned char *)s1;
	s2unsigned = (unsigned char *)s2;
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1unsigned[i] != s2unsigned[i])
			return (s1unsigned[i] - s2unsigned[i]);
		i++;
	}
	return (0);
}
