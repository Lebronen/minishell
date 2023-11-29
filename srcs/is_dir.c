/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:23:04 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/29 18:23:48 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *commande)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	while (commande[i])
	{
		if (commande[i] == '/')
			point = 0;
		else if (commande[i] == '.')
			point++;
		else
			return (0);
		if (point > 2)
			return (0);
		i++;
	}
	return (1);
}
