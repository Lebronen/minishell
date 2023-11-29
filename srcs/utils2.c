/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:04:17 by rshay             #+#    #+#             */
/*   Updated: 2023/11/29 18:28:17 by rshay            ###   ########.fr       */
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
	while (commande[i] != c)
		i++;
	return (i);
}
