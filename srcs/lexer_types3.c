/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <cgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:03:29 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/19 15:03:32 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handlenothing(t_token **last)
{
	(*last) = new_token(COMMAND, " ", (*last));
}

int	has_quote(char *commande)
{
	int	i;

	i = 0;
	while (commande[i] && commande[i] != ' ')
	{
		if (commande[i] == 39)
		{
			i++;
			while (commande[i] != 39)
				i++;
			return (i);
		}
		else if (commande[i] == '"')
		{
			i++;
			while (commande[i] != '"')
				i++;
			return (i);
		}
		i++;
	}
	return (0);
}

char	*manage_quotes_p2(char *commande, int i, char c)
{
	int		j;
	char	*str;

	j = i;
	i -= 2;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	str[i +1] = '\0';
	while (i >= 0)
	{
		if (commande[j] != c)
		{
			str[i] = commande[j];
			i--;
			j--;
		}
		else
			j--;
	}
	return (str);
}

char	*manage_with_quote(char *commande)
{
	int	i;

	i = 0;
	while (commande[i])
	{
		if (commande[i] == '"')
		{
			i++;
			while (commande [i] && commande[i] != '"')
				i++;
			return (manage_quotes_p2(commande, i, '"'));
		}
		else if (commande[i] == 39)
		{
			i++;
			while (commande [i] && commande[i] != 39)
				i++;
			return (manage_quotes_p2(commande, i, 39));
		}
		else
			i++;
	}
	return (commande);
}
