/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:27:16 by vegret            #+#    #+#             */
/*   Updated: 2022/11/08 13:51:30 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	strcontains(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static size_t	end(char const *s1, char const *set)
{
	size_t	end;

	end = ft_strlen(s1) - 1;
	while (strcontains(set, s1[end]))
		end--;
	return (++end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		i;
	size_t	j;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = end(s1, set);
	while (s1[i] && len)
	{
		if (!strcontains(set, s1[i++]))
			break ;
		len--;
	}
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i--;
	j = 0;
	while (s1[i] && j < len)
		result[j++] = s1[i++];
	result[j] = '\0';
	return (result);
}
