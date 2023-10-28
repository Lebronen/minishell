/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <cgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:03:11 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/19 15:03:15 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handlepipetoken(int i, t_token **last)
{
	(*last) = new_token(PIPE, NULL, (*last));
	(*last)->type_2 = 8;
	i++;
	return (i);
}

int	handleinputredir(int i, t_token **last, char *commande)
{
	if (commande[i + 1] == '<')
	{
		(*last) = new_token(REDIR, "EOF", (*last));
		(*last)->type_2 = ENDOF;
		i ++;
	}
	else
	{
		(*last) = new_token(REDIR, "input", (*last));
		(*last)->type_2 = IN;
	}
	i++;
	if (commande[i] == '|' || commande[i] == '\\' || commande[i] == '$')
		i++;
	return (i);
}

int	handleoutputredir(int i, t_token **last, char *commande)
{
	if (commande[i + 1] == '>')
	{
		(*last) = new_token(REDIR, "Append", (*last));
		(*last)->type_2 = APPEND;
		i ++;
	}
	else
	{
		(*last) = new_token(REDIR, "Output", (*last));
		(*last)->type_2 = OUT;
	}
	i++;
	if (commande[i] == '|' || commande[i] == '\\' || commande[i] == '$')
		i++;
	return (i);
}
