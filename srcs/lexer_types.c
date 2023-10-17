/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:31:31 by cgermain          #+#    #+#             */
/*   Updated: 2023/09/25 11:13:36 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handlePipeToken(int i, t_token **last)
{
    (*last) = new_token(PIPE, NULL, (*last));
    (*last)->type_2 = 8;
    i++;
    return (i);
}

int handleInputRedir(int i, t_token **last,char *commande)
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
    return (i);
}

int handleOutputRedir(int i, t_token **last, char *commande)
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
    return (i);
}

int handleDoubleQuoteToken(int i, t_token **last, char *commande)
{
    i++;
	(*last) = new_token(QUOTE, ft_strdup_c(&commande[i], 34), (*last));
	while (commande[i] != 34 && commande[i] != '\0')
		i++;
	if (commande[i] == 34)
	    i++;
    return (i);
}

int handleSingleQuoteToken(int i, t_token **last, char *commande)
{
    i++;
	(*last) = new_token(QUOTE, ft_strdup_c(&commande[i], 39), (*last));
	while (commande[i] != 39 && commande[i] != '\0')
		i++;
	if (commande[i] == 39)
		i++;
    return (i);
}

int handleWordToken(int i, t_token **last, char *commande)
{
    (*last) = new_token(WORD, ft_strdup_c(&commande[i], 32), (*last)); 
	while (commande[i] != 32 && commande[i] != '\0' && commande[i] != '>' &&commande[i] != '<')
		i++;
    return (i);
}
