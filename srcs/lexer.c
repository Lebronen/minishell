/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:49:44 by cgermain          #+#    #+#             */
/*   Updated: 2023/09/21 19:51:55 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_token *new_token(int type, char *str, t_token *last)
{
	t_token *new;


	new = malloc(sizeof(t_token));
	if(!new)
		return (NULL);
	new->type = type;
	new->str = str;
	new->previous = last;
	new->next = NULL;
	return (new);
}

char *getstring(char *str, char c)
{
	int	i;
	char	*result;

	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (str[i] != c || str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
 	


t_token	*lexer(char *commande)
{
	int	i;

	t_token *last;
	last = NULL;
	i = 0;
	while (commande[i])
	{
		if (commande[i] == ' ')
			i++;
		else if (commande[i] == '|')
		{
			last = new_token(PIPE, NULL, last);
			i++;
		}
		else if (commande[i] == ('<'))
		{
			if (commande[i + 1] == '<')
			{
				last = new_token(REDIR, "EOF", last);
				i++;
			}
			else
				last = new_token(REDIR, "input", last);
			i++;
		}
		else if (commande[i] == ('>'))
		{
			if (commande[i + 1] == '>')
			{
				last = new_token(REDIR, "Append", last);
				i++;
			}
			else
				last = new_token(REDIR, "Output", last);
			i++;
		}
	/*	else if (commande[i]  == 34)
		{
			i++;
			last = new_token(QUOTE, getstring(commande + i, 34), last);
			while (commande[i] != 34 && commande[i] != '\0')
				i++;
			//printf("lol");
			//i++;
		}*/
		else
		{
		/*	last = new_token(WORD, getstring(commande + i, 32), last); 
			while (commande[i] != 32 && commande[i] != '\0')
				i++;*/
			printf("lol");
			i++;
		}
	}
	return (last);
}
