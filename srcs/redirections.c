/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <cgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:05:03 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/19 15:05:09 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_out(t_token *token)
{
	int	fd;

	fd = -1;
	while (token && token->type != PIPE)
	{
		if (token->type_2 == OUT)
		{
			if (fd != -1)
				close(fd);
			fd = open(token->next->str, O_TRUNC | O_CREAT, 0644);
			if (fd == -1)
				return (-1);
		}
		if (token->type_2 == APPEND)
		{
			if (fd != -1)
				close(fd);
			fd = open(token->next->str, O_APPEND | O_CREAT, 0644);
			if (fd == -1)
				return (-1);
		}
		token = token->next;
	}
	return (fd);
}

int	has_heredoc(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type_2 == EOF)
			return (1);
		token = token->next;
	}
	return (0);
}

int	number_heredoc(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type_2 == ENDOF)
			i++;
		token = token->next;
	}
	return (i);
}

void	manage_heredoc(t_node *node, t_token *token)
{
	int		i;
	t_token	*tmp_token;

	tmp_token = token;
	if (node->fd_in != -2)
	{
		node->heredoc = NULL;
		return ;
	}
	i = number_heredoc(token);
	node->heredoc = malloc(sizeof(char *) * (i + 1));
	if (!node->heredoc)
		return ;
	i = 0;
	while (tmp_token)
	{
		if (tmp_token->type_2 == ENDOF)
		{
			node->heredoc[i] = ft_strdup(tmp_token->next->str);
			i++;
		}
		tmp_token = tmp_token->next;
	}
	node->heredoc[i] = NULL;
}

int	init_in(t_token *token)
{
	int	fd;

	fd = -1;
	while (token && token->type != PIPE)
	{
		if (token->type_2 == IN)
		{
			if (fd != -1 && fd != -2)
				close(fd);
			fd = open(token->next->str, O_RDONLY);
			if (fd == -1)
				return (input_error(token->next->str));
		}
		else if (token->type_2 == ENDOF)
		{
			if (fd != -1 && fd != -2)
				close(fd);
			return (-2);
		}
		token = token->next;
	}
	return (fd);
}
