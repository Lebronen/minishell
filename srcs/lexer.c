/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:49:44 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/03 15:10:12 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_c(char *s, char c)
{
	char	*result;
	int		i;

	result = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c && s[i] != '>' && s[i] != '<' && s[i] != '|')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	tokenizer_first_token(t_token *token)
{
	if (token->type == REDIR)
		token->next->type_2 = PATH;
	else
		token->type_2 = COMMAND;
	return (1);
}

void	tokenizer(t_token *token)
{
	if (!tokenizer_first_token(token))
		return ;
	token = token->next;
	while (token != NULL)
	{
		if ((token->type == WORD || token->type == QUOTE)
			&& token->previous->type != REDIR)
		{
			if (token->previous->type == PIPE
				|| token->previous->type_2 == PATH)
				token->type_2 = COMMAND;
			else if (token->str[0] == '-')
				token->type_2 = OPTION;
			else
				token->type_2 = ARG;
		}
		if (token->type == REDIR)
			token->next->type_2 = PATH;
		token = token->next;
	}
}

int	handlecommande(int i, t_token **last, char *commande)
{
	if (commande[i] == '<')
		i = handleinputredir(i, last, commande);
	else if (commande[i] == '>')
		i = handleoutputredir(i, last, commande);
	else if (commande[i] == 34)
		i = handledoublequotetoken(i, last, commande);
	else if (commande[i] == 39)
		i = handlesinglequotetoken(i, last, commande);
	else
		i = handlewordtoken(i, last, commande);
	return (i);
}

t_token	*lexer(char *commande, t_data *data)
{
	int		i;
	t_token	*last;

	i = 0;
	last = NULL;
	if (error_ambig(commande, data))
		return (NULL);
	while (commande[i])
	{
		if (commande[i] == ' ')
			i++;
		else if (commande[i] == '|')
			i = handlepipetoken(i, &last);
		else
			i = handlecommande(i, &last, commande);
	}
	last->next = NULL;
	tokenizer(first_token(last));
	return (first_token(last));
}

/*
void print_token(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
		{
			printf("<PIPE>\n");
		}
		else if (token->type == REDIR)
		{
			if (token->type_2 == IN)
				printf("<IN>\n");
			if (token->type_2 == OUT)
				printf("<OUT>\n");
			if (token->type_2 == ENDOF)
				printf("<EOF>\n");
			if (token->type_2 == APPEND)
				printf("<APPEND>\n");
		}
		else
		{
			if (token->type_2 == PATH)
				printf("<%s>, <type = path>\n", token->str);
			if (token->type_2 == COMMAND)
				printf("<%s>, <type = command>\n", token->str);
			if (token->type_2 == OPTION)
				printf("<%s>, <type = option>\n", token->str);
			if (token->type_2 == ARG)
				printf("<%s>, <type = arg>\n", token->str);
		}
		token = token->next;
	}
}*/