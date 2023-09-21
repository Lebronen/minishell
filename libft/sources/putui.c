/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:17:44 by vegret            #+#    #+#             */
/*   Updated: 2022/12/27 03:57:17 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	uintlen(unsigned int n)
{
	int	len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	putui_aux(int fd, unsigned int n)
{
	if (n < 10)
		return (putchar_c(fd, n + '0', NULL));
	return (putui_aux(fd, n / 10) + putui_aux(fd, n % 10));
}

static int	printinglen(unsigned int n, t_flag *flag)
{
	int	len;

	len = uintlen(n);
	if (flag && flag->flags & DOT && flag->precision > len)
		len = flag->precision;
	if (n == 0 && flag && flag->flags & DOT && flag->precision == 0)
		len = 0;
	return (len);
}

int	putui(int fd, unsigned int n, t_flag *flag)
{
	int	printed;

	printed = 0;
	if (!(flag && flag->flags & ZERO))
		printed = fill_before(fd, flag, printinglen(n, flag));
	printed += putzeros(fd, flag, uintlen(n), 0);
	if (n == 0 && flag && flag->flags & DOT && flag->precision == 0)
		return (printed);
	if (n < 10)
		printed += putui_aux(fd, n);
	else
		printed += putui_aux(fd, n / 10) + putui_aux(fd, n % 10);
	return (printed);
}
