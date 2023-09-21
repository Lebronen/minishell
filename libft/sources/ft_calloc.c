/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:01:37 by vegret            #+#    #+#             */
/*   Updated: 2022/11/08 12:06:20 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (size > 0 && nmemb > ULLONG_MAX / size)
		return (NULL);
	result = malloc(nmemb * size);
	if (result)
		ft_bzero(result, nmemb * size);
	return (result);
}
