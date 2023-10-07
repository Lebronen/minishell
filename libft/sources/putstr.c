/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:00:48 by rshay            #+#    #+#             */
/*   Updated: 2022/12/27 03:16:44 by rshay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_c(int fd, char c, t_flag *flag)
{
	return (fill_before(fd, flag, 1) + write(fd, &c, 1));
}

static int	nstrlen(char *str, t_flag *flag)
{
	int	len;

	if (flag && flag->flags & DOT && 6 > flag->precision && !str)
		return (0);
	if (!str)
		return (6);
	len = 0;
	while (str[len])
		len++;
	if (flag && flag->flags & DOT && len > flag->precision)
		len = flag->precision;
	return (len);
}

int	putstr(int fd, char *str, t_flag *flag)
{
	int	printed;
	int	i;

	printed = fill_before(fd, flag, nstrlen(str, flag));
	if (!str)
	{
		if (!(flag && flag->flags & DOT && flag->precision < 6))
			printed += (write(fd, "(null)", 6));
	}
	else
	{
		i = 0;
		while (str[i])
		{
			if (flag && flag->flags & DOT && i >= flag->precision)
				return (printed);
			printed += write(fd, &str[i], 1);
			i++;
		}
	}
	return (printed);
}
