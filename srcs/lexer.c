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

t_token *first_token(t_token *token)
{
	t_token *previous;

	while (token->previous)
	{
		previous = token->previous;
		previous->next = token;
		token = token->previous;
	}
	return(token);
}

char	*ft_strdup_c(char *s, char c)
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
	if (s[i] == '\0' && (c == 39 || c == 34))
	{
		write(2, "il faut fermer les guillemets", 29);
		return (NULL);
	}
	return (result);
}
 	
void tokenizer(t_token *token)
{
	
	if (token->type == PIPE)
	{
		printf("parse error near '|'");
		return ;
	}
	if (token->type == REDIR)
	{
		token = token->next;
		token->type_2 = PATH;
	}
	else
	{
		token->type_2 = COMMAND;
		token = token->next;
	}
	while (token != NULL)
	{
		if ((token->type == WORD || token->type == QUOTE) && token->previous->type != REDIR)
		{
			if (token->previous->type == PIPE || token->previous->type_2 == PATH)
				token->type_2 = COMMAND;
			else if (token->str[0]== '-')
				token->type_2 = OPTION;
			else
				token->type_2 = ARG; 
		}
		if (token->type == REDIR)
			token->next->type_2 = PATH;
		token = token->next;
	}
}

char *new_command(char *commande, char *env_value, int i)
{
	size_t j;
	size_t	k;
	size_t l;
	char *str;
	
	j = 0;
	k = i;
	l = 0;

	while(commande[i] != ' ' && commande[i] != '\0' && commande[i] != '"')
		i++;
	str = malloc(sizeof(char) * ((ft_strlen(commande) - (i-k)) + ft_strlen(env_value)));
	if(!str)
		return (NULL);
	while (j < k)
	{
		str[j] = commande[j];
		j++;
	}
	while(j < (ft_strlen(env_value) + k))
	{
		str[j] = env_value[l];
		j++;
		l++;
	}
	while(commande[i])
	{
		str[j] = commande[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free(commande);
	return str;
}

char *env_value_checker(char *commande, t_list *envp)
{
	int i;
	int j;

	i = 0;
	while (commande[i])
	{
		if (commande[i] == 39)
		{
			i++;
			while(commande[i] && commande[i] != 39)
				i++;
			if (commande[i] == 39)
			i++;
		}
		else if (commande[i] == '"')
		{
			i++;
			while(commande[i] && commande[i] != '"')
			{
				if (commande[i] == '$')
				{
					i++;
					j = i;
					while (commande[i] && commande[i] != ' ' && commande[i] != '"')
						i++;
					if (commande[i] == '"')
						commande = new_command(commande, get_env_value(envp, ft_strdup_c(&commande[j], '"')), j - 1);
					else
						commande = new_command(commande, get_env_value(envp, ft_strdup_c(&commande[j], ' ')), j - 1);
				}
				i++;
			}
			if(commande[i] == '"')
				i++;
		}
		else if (commande[i] == '$')
		{
			i++;
			commande = new_command(commande, get_env_value(envp, ft_strdup_c(&commande[i], ' ')), i - 1);
			while (commande[i] && commande[i] != ' ')
				i++;
		}
		else 
			i++;
	}
	return (commande);
}

//gerer unclosed quotes "

t_token	*lexer(char *commande, t_list *envp)
{
	int	i;
	t_token *last;

	last = NULL;
	i = 0;
	
	commande = env_value_checker(commande, envp);
	while (commande[i])
	{
		if (commande[i] == ' ')
			i++;
		else if (commande[i] == '|')
		{
			last = new_token(PIPE, NULL, last);
			last->type_2 = 0;
			i++;
		}
		else if (commande[i] == ('<'))
		{
			if (commande[i + 1] == '<')
			{
				last = new_token(REDIR, "EOF", last);
				last->type_2 = ENDOF;
				i++;
			}
			else
			{
				last = new_token(REDIR, "input", last);
				last->type_2 = IN;
			}
			i++;
		}
		else if (commande[i] == ('>'))
		{
			if (commande[i + 1] == '>')
			{
				last = new_token(REDIR, "Append", last);
				last->type_2 = APPEND;
				i++;
			}
			else
			{
				last = new_token(REDIR, "Output", last);
				last->type_2 = OUT;
			}
			i++;
		}
		else if (commande[i]  == 34)
		{
			i++;
			last = new_token(QUOTE, ft_strdup_c(&commande[i], 34), last);
			while (commande[i] != 34 && commande[i] != '\0')
				i++;
			if (commande[i] == 34)
				i++;

		}
		else if (commande[i]  == 39)
		{
			i++;
			last = new_token(QUOTE, ft_strdup_c(&commande[i], 39), last);
			while (commande[i] != 39 && commande[i] != '\0')
				i++;
			if (commande[i] == 39)
				i++;
		}
		else
		{
			last = new_token(WORD, ft_strdup_c(&commande[i], 32), last); 
			while (commande[i] != 32 && commande[i] != '\0')
				i++;
		}
	}
	last->next = NULL;
	tokenizer (first_token(last));
	return (first_token(last));
}


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
}