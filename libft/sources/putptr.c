/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:44:33 by rshay            #+#    #+#             */
/*   Updated: 2023/02/07 22:54:51 by rshay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ptrlen(void *ptr, t_flag *flag)
{
	int	len;

	if (!ptr)
		return (5);
	len = hexlen((unsigned long) ptr);
	if (flag && flag->flags & DOT && flag->precision > len)
		len = flag->precision;
	len += (flag->flags & SPACE || flag->flags & PLUS);
	return (2 + len);
}

int	putptr(int fd, void *ptr, t_flag *flag)
{
	int	printed;

	printed = 0;
	if (flag && !(flag->flags & ZERO))
		printed = fill_before(fd, flag, ptrlen(ptr, flag));
	if (!ptr)
		printed += write(fd, "(nil)", 5);
	else
	{
		if (flag && flag->flags & SPACE)
			printed += write(fd, " ", 1);
		if (flag && flag->flags & PLUS)
			printed += write(fd, "+", 1);
		printed += write(fd, "0x", 2);
		printed += putul_hex(fd, (unsigned long) ptr, 0, NULL);
	}
	return (printed);
}
