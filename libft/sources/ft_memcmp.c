/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:42:34 by vegret            #+#    #+#             */
/*   Updated: 2022/11/08 13:18:33 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!n)
		return (0);
	while (*((unsigned char *) s1) == *((unsigned char *) s2) && --n)
	{
		s1++;
		s2++;
	}
	return (*((unsigned char *) s1) - *((unsigned char *) s2));
}
