/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:04:17 by rshay             #+#    #+#             */
/*   Updated: 2023/12/05 16:39:07 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *content)
{
	content = NULL;
	free(content);
}

int	ft_index(char *commande, char c)
{
	int	i;

	i = 0;
	while (commande[i] && commande[i] != c)
		i++;
	if (!commande[i])
		return (-1);
	return (i);
}
