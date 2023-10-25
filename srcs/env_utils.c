/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:11:17 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/25 12:11:22 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_cleaner(char *name)
{
	int		i;
	int		j;
	char	*name2;

	i = 0;
	j = 0;
	while (name[j])
		j++;
	if (name[j - 1] == '}' && name[i] == '{')
		i = 2;
	if (i != 2)
		return (name);
	name2 = malloc(sizeof(char) * (ft_strlen(name) - i + 1));
	if (!name2)
		return (NULL);
	i = 1;
	while (name[i] != '}')
	{
		name2[i - 1] = name[i];
		i++;
	}
	name2[i - 1] = '\0';
	return (name2);
}
