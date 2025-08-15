/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:22:17 by epakdama          #+#    #+#             */
/*   Updated: 2025/06/23 08:01:29 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(unsigned long nbr, char *base, int *len)
{
	int		i;
	char	buffer[65];

	if (nbr == 0)
	{
		ft_putchar(base[0], len);
		return ;
	}
	i = 0;
	while (nbr > 0)
	{
		buffer[i++] = base[nbr % 16];
		nbr /= 16;
	}
	while (i-- > 0)
		ft_putchar(buffer[i], len);
}
