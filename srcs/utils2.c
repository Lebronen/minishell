/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:04:17 by rshay             #+#    #+#             */
/*   Updated: 2023/12/18 22:50:47 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	syntax_error(t_data *data, char *commande, int i)
{
	char	c;
	int		quotes1;
	int		quotes2;

	quotes1 = 0;
	quotes2 = 0;
	while (commande[i])
	{
		if (commande[i] != ' ' && commande[i] != 9)
			c = commande[i];
		if ((quotes2 % 2 == 0) && commande[i] == '"')
			quotes1++;
		if ((quotes1 % 2 == 0) && commande[i] == '\'')
			quotes2++;
		i++;
	}
	if (c == '|' || c == '>' || c == '<'
		|| quotes1 % 2 != 0 || quotes2 % 2 != 0)
		return (print_error(2, NULL, "Syntax error\n", data));
	else
		return (0);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
