/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:15:41 by vegret            #+#    #+#             */
/*   Updated: 2022/12/22 16:43:29 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == 32 || (c > 8 && c < 14));
}

int	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (ft_isdigit(nptr[i]))
	{
		if (result > (LONG_MAX / 10))
			return (-1 * (sign == 1));
		result = result * 10 + nptr[i++] - 48;
		if (result < 0)
			return (-1 * (sign == 1));
	}
	return (result * sign);
}
