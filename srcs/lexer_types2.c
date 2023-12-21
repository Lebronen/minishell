/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:03:29 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/29 14:47:28 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup_c2(char *s, char c)
{
	char	*result;
	int		i;

	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup_c3(char *s, char c)
{
	char	*result;
	int		i;

	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	handledoublequotetoken(int i, t_token **last, char *commande)
{
	i++;
	(*last) = new_token(QUOTE, ft_strdup_c2(&commande[i], 34), (*last));
	while (commande[i] != 34 && commande[i] != '\0')
		i++;
	if (commande[i] == 34)
		i++;
	if (!(*last))
		return (-1);
	return (i);
}

int	handlesinglequotetoken(int i, t_token **last, char *commande)
{
	i++;
	(*last) = new_token(QUOTE, ft_strdup_c2(&commande[i], 39), (*last));
	while (commande[i] != 39 && commande[i] != '\0')
		i++;
	if (commande[i] == 39)
		i++;
	if (!(*last))
		return (-1);
	return (i);
}

int	handlewordtoken(int i, t_token **last, char *commande)
{
	if (commande[i] == '$' && commande[i + 1]
		&& commande [i + 1] != ' ' && commande [i + 1] != '"')
		(*last) = new_token(WORD, ft_strdup(""), (*last));
	else if (has_quote(&commande[i]))
	{
		(*last) = new_token(WORD, manage_with_quote(&commande[i]), (*last));
		return (has_quote(&commande[i]) + i +1);
	}
	else
		(*last) = new_token(WORD, ft_strdup_c(&commande[i], 32), (*last));
	if (!(*last))
		return (-1);
	while (commande[i] != 32 && commande[i] != '\0'
		&& commande[i] != '>' && commande[i] != '<' && commande[i] != '|')
		i++;
	return (i);
}
