/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:57:01 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/24 11:57:07 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_cmd(char *commande)
{
	int		i;
	char	c;

	i = 0;
	if (!commande[i])
		return (1);
	while (commande[i])
	{
		if (commande[i] != ' ')
			c = commande[i];
		i++;
	}
	if (c == '|' || c == '>' || c == '<')
	{
		write(2, "Syntax Error\n", 13);
		return (1);
	}
	return (0);
}

int	input_error(char *str)
{
	write(2, "'", 1);
	ft_putstr_fd(str, 2);
	write(2, "' : No such file or directory\n", 30);
	return (-1);
}
