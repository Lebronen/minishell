/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:14:40 by rshay            #+#    #+#             */
/*   Updated: 2022/12/27 04:31:09 by rshay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* TODO
- Finir
- norme
- handle write fail
*/
static int	ft_vdprintf(int fd, const char *format, va_list args)
{
	int		i;
	int		count;
	t_flag	flag;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			i += handle_flags(format + i, &flag);
			count += handle_conv(fd, format + i, args, &flag);
		}
		else
			count += write(fd, &format[i], 1);
		i++;
	}
	return (count);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		count;
	va_list	args;

	va_start(args, format);
	count = ft_vdprintf(fd, format, args);
	va_end(args);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	args;

	va_start(args, format);
	count = ft_vdprintf(1, format, args);
	va_end(args);
	return (count);
}
