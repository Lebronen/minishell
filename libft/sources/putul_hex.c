/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putul_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:18:28 by rshay            #+#    #+#             */
/*   Updated: 2022/12/27 03:58:39 by rshay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define HEXVALS "0123456789abcdef"
#define UPPERHEXVALS "0123456789ABCDEF"

int	hexlen(unsigned long n)
{
	int	len;

	len = 1;
	while (n > 15)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static int	putul_hex_aux(int fd, unsigned long n, int u)
{
	if (n < 16)
	{
		if (u)
			return (write(fd, &UPPERHEXVALS[n], 1));
		return (write(fd, &HEXVALS[n], 1));
	}
	return (putul_hex_aux(fd, n / 16, u) + putul_hex_aux(fd, n % 16, u));
}

static int	printinglen(unsigned long n, t_flag *flag)
{
	int	len;

	len = hexlen(n);
	if (flag && flag->flags & DOT && flag->precision > len)
		len = flag->precision;
	if (n == 0 && flag && flag->flags & DOT && flag->precision == 0)
		len = 0;
	len += 2 * (flag && flag->flags & SHARP && n > 0);
	return (len);
}

int	putul_hex(int fd, unsigned long n, int u, t_flag *flag)
{
	int	printed;

	printed = 0;
	if (!(flag && flag->flags & ZERO))
		printed = fill_before(fd, flag, printinglen(n, flag));
	if (flag && flag->flags & SHARP && n > 0)
	{
		if (u)
			printed += write(fd, "0X", 2);
		else
			printed += write(fd, "0x", 2);
	}
	printed += putzeros(fd, flag, hexlen(n), printed);
	if (n == 0 && flag && flag->flags & DOT && flag->precision == 0)
		return (printed);
	if (n < 16)
		printed += putul_hex_aux(fd, n, u);
	else
		printed += putul_hex_aux(fd, n / 16, u) + putul_hex_aux(fd, n % 16, u);
	return (printed);
}
