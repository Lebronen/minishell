/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:54:25 by rshay            #+#    #+#             */
/*   Updated: 2022/11/08 12:37:31 by rshay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	j;
	size_t	i;

	if (*s2 == '\0')
		return ((char *) s1);
	i = 0;
	while (i < len && s1[i])
	{
		j = 0;
		while (i + j < len && s2[j] == s1[i + j])
		{
			j++;
			if (s2[j] == '\0')
				return ((char *) s1 + i);
		}
		i++;
	}
	return (NULL);
}
