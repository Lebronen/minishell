/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 16:55:46 by vegret            #+#    #+#             */
/*   Updated: 2022/11/08 13:50:58 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	intlen(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	while (n > 9 || n < -9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_abs(int n)
{
	return (n * (-1 + 2 * (n > 0)));
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;
	int		sign;

	len = intlen(n);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	sign = (n > 0);
	*result = '0';
	if (n < 0)
		*result = '-';
	result += len;
	*result-- = '\0';
	while (n != 0)
	{
		*result-- = '0' + ft_abs(n % 10);
		n /= 10;
	}
	return (result + sign);
}
