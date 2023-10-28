/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <cgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:03:45 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/19 15:03:49 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(int type, char *str, t_token *last)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->str = str;
	new->previous = last;
	new->next = NULL;
	return (new);
}

t_token	*first_token(t_token *token)
{
	t_token	*previous;

	while (token->previous)
	{
		previous = token->previous;
		previous->next = token;
		token = token->previous;
	}
	return (token);
}

void	free_lexer(t_token *token)
{
	t_token	*tmp_token;

	while (token && token->previous)
	{
		token = token->previous;
	}
	while (token)
	{
		tmp_token = token->next;
		if (token->type == QUOTE || token->type == WORD)
			free(token->str);
		free(token);
		token = tmp_token;
	}
}
