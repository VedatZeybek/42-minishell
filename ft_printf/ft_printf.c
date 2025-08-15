/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epakdama <epakdama@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:29:38 by epakdama          #+#    #+#             */
/*   Updated: 2025/06/19 14:16:59 by epakdama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	write_variadic(char *s, int i, va_list args, int *len)
{
	void	*ptr;

	if (s[i + 1] == 's')
		ft_putstr(va_arg(args, char *), len);
	else if (s[i + 1] == 'c')
		ft_putchar(va_arg(args, int), len);
	else if (s[i + 1] == 'i' || s[i + 1] == 'd')
		ft_putnbr(va_arg(args, int), len);
	else if (s[i + 1] == 'u')
		ft_putunsigned(va_arg(args, unsigned int), len);
	else if (s[i + 1] == 'p')
	{
		ptr = va_arg(args, void *);
		if (ptr == NULL)
			ft_putstr("(nil)", len);
		else
		{
			ft_putstr("0x", len);
			ft_putnbr_base((unsigned long)ptr, LOWER_BASE, len);
		}
	}
	else if (s[i + 1] == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), LOWER_BASE, len);
	else if (s[i + 1] == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), UPPER_BASE, len);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	int		i;
	va_list	args;

	len = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] != '%')
			ft_putchar(s[i], &len);
		else if (s[i + 1] == '\0')
			break ;
		else if (s[i + 1] == '%')
			ft_putchar(s[i++], &len);
		else
			write_variadic((char *)s, i++, args, &len);
		i++;
	}
	va_end(args);
	return (len);
}
