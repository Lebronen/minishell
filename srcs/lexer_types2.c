/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <cgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:03:29 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/19 15:03:32 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handledoublequotetoken(int i, t_token **last, char *commande)
{
	i++;
	(*last) = new_token(QUOTE, ft_strdup_c(&commande[i], 34), (*last));
	while (commande[i] != 34 && commande[i] != '\0')
		i++;
	if (commande[i] == 34)
		i++;
	return (i);
}

int	handlesinglequotetoken(int i, t_token **last, char *commande)
{
	i++;
	(*last) = new_token(QUOTE, ft_strdup_c(&commande[i], 39), (*last));
	while (commande[i] != 39 && commande[i] != '\0')
		i++;
	if (commande[i] == 39)
		i++;
	return (i);
}

int	handlewordtoken(int i, t_token **last, char *commande)
{
	(*last) = new_token(WORD, ft_strdup_c(&commande[i], 32), (*last));
	while (commande[i] != 32 && commande[i] != '\0'
		&& commande[i] != '>' && commande[i] != '<')
		i++;
	return (i);
}
