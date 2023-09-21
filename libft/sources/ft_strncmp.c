/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:11:27 by vegret            #+#    #+#             */
/*   Updated: 2022/12/21 13:11:45 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	if (!n)
		return (0);
	i = 0;
	while (--n && s1[i] && s2[i])
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			break ;
		i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
