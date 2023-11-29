/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_envbis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:55:34 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/13 16:55:35 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	env_value_quote1(int i, char**commande, t_data *data)
{
	while ((*commande)[i] != '"')
	{
		i++;
		if ((*commande)[i - 1] == 39)
		{
			while ((*commande)[i] && (*commande)[i] != 39)
				i++;
			if ((*commande)[i] == 39)
			i++;
		}
		else if ((*commande)[i - 1] == 92)
			i = env_value_backslash(i, commande);
		else if ((*commande)[i - 1] == '$')
			i = env_value_dollar(i, commande, data);
	}
	return (i);
}

int	env_value_quote2(int i, char **commande)
{
	int		j;
	int		k;
	char	*str1;

	k = 0;
	i++;
	if ((*commande)[i] == '$')
		k = 1;
	j = i;
	while ((*commande)[i] &&
		(*commande)[i] != ' ' && (*commande)[i] != '"')
			i++;
	if ((*commande)[i] == '"')
		str1 = ft_strdup_c(&(*commande)[j], '"');
	else
		str1 = ft_strdup_c(&(*commande)[j], ' ');
	(*commande) = new_command((*commande), str1, j - k);
	free(str1);
	return (i);
}

int	env_value_quote(int i, char **commande, t_data *data)
{	
	while ((*commande)[i] && (*commande)[i] != '"')
			i = env_value_quote1(i, commande, data);
	return (i);
}

