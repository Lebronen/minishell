/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:05:26 by rshay            #+#    #+#             */
/*   Updated: 2022/11/08 18:08:41 by rshay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	l;

	if (!dst)
		l = 0;
	else
		l = ft_strlen(dst);
	if (l > size)
		l = size;
	if (!size || l == size)
		return (l + ft_strlen(src));
	return (l + ft_strlcpy(dst + l, src, size - l));
}
