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

size_t	boost_i(char *commande, size_t i)
{
	i++;
	while (commande[i] != ' ' && commande[i] != '\0' && commande[i] != '"'
		&& commande[i] != '$' && commande[i] != 39)
		i++;
	return (i);
}

int	env_value_quote1(int i, char**commande, t_data *data)
{
	while ((*commande)[i] && (*commande)[i] != '"')
	{
		i++;
		if ((*commande)[i - 1] == 39)
		{
			while ((*commande)[i] && (*commande)[i] != 39)
				i++;
			if ((*commande)[i] == 39)
			i++;
		}
		else if ((*commande)[i - 1] == '$')
			i = env_value_dollar(i, commande, data);
	}
	return (i);
}

int	env_value_quote(int i, char **commande, t_data *data)
{	
	while ((*commande)[i] && (*commande)[i] != '"')
			i = env_value_quote1(i, commande, data);
	return (i);
}

void	free_str(char *str, char *str1)
{
	if (str)
		free(str);
	if (str1)
		free(str1);
}
