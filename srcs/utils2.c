/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:04:17 by rshay             #+#    #+#             */
/*   Updated: 2023/12/20 12:31:11 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp2(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
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

int	ft_str_only_ncmp(char *s1, char *s2, int n)
{
	return (!ft_strncmp(s1, s2, n) && ft_strcmp(s1 + n, s2 + n));
}
