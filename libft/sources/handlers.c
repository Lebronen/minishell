/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:20:23 by rshay            #+#    #+#             */
/*   Updated: 2022/12/27 03:17:24 by rshay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_atoi(const char *s, int *i)
{
	int	r;

	r = 0;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		r = r * 10 + s[*i] - '0';
		(*i)++;
	}
	return (r);
}

static int	strindex(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_pow(int n, int k)
{
	if (k < 0)
		return (0);
	if (k == 0)
		return (1);
	if (k == 1)
		return (n);
	return (n * ft_pow(n, k - 1));
}

int	handle_flags(const char *s, t_flag *flag)
{
	int	skipped;
	int	index;

	flag->flags = 0;
	flag->minimal_width = 0;
	flag->precision = 0;
	index = strindex(FLAGS, *s);
	skipped = 0;
	while (index != -1 && s[skipped])
	{
		flag->flags |= ft_pow(2, index);
		index = strindex(FLAGS, s[++skipped]);
	}
	flag->minimal_width = ft_atoi(s, &skipped);
	if (s[skipped] == '.')
	{
		skipped++;
		flag->flags |= DOT;
		flag->precision = ft_atoi(s, &skipped);
	}
	flag->flags = make_compatibility(flag->flags);
	return (skipped);
}

int	handle_conv(int fd, const char *s, va_list args, t_flag *flag)
{
	int	printed;

	printed = 0;
	if (*s == 'c')
		printed += putchar_c(fd, va_arg(args, int), flag);
	else if (*s == 's')
		printed += putstr(fd, va_arg(args, char *), flag);
	else if (*s == 'p')
		printed += putptr(fd, va_arg(args, void *), flag);
	else if (*s == 'd' || *s == 'i')
		printed += putint(fd, va_arg(args, int), flag);
	else if (*s == 'u')
		printed += putui(fd, va_arg(args, unsigned int), flag);
	else if (*s == 'x' || *s == 'X')
		printed += putul_hex(fd, va_arg(args, unsigned int), *s == 'X', flag);
	else if (*s == '%')
		return (write(fd, "%", 1));
	return (printed + fill_after(fd, flag, printed));
}
