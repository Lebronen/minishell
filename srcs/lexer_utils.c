/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:03:45 by cgermain          #+#    #+#             */
/*   Updated: 2023/12/19 16:13:21 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(int type, char *str, t_token *last)
{
	t_token	*new;

	if (str == NULL && type != PIPE)
		return (NULL);
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

	if (!token)
		return ;
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

int	has_prev_cmd(t_token *token)
{
	token = token->previous;
	while (token && token->type != PIPE)
	{
		if (token->type_2 == COMMAND)
			return (1);
		if (token->previous)
			token = token->previous;
		else
			return (0);
	}
	return (0);
}

t_token	*malloc_error_token(t_token *token)
{
	if (token)
		free_lexer(first_token(token));
	return (NULL);
}
