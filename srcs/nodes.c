/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:24:28 by cgermain          #+#    #+#             */
/*   Updated: 2023/12/04 22:22:23 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_str(t_token *token, char **str)
{
	int	i;

	i = 0;
	if (token->str[0])
	{
		str[0] = ft_strdup(token->str);
		i++;
	}
	token = token->next;
	while (token && (token->type_2 == OPTION || token->type_2 == ARG))
	{
		if (token->str[0])
		{
			str[i] = ft_strdup(token->str);
			i++;
		}
		token = token->next;
	}
	str[i] = NULL;
	if (str)
		return (str);
	return (NULL);
}

t_node	*make_cmd(t_token *token)
{
	t_node	*node;
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_token = token;
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	while (token->next && (token->next->type_2 == OPTION
			|| token->next->type_2 == ARG))
	{
		if (!ft_strcmp(token->next->str, ""))
			i++;
		token = token->next;
	}
	node->str_options = malloc((i + 2) * sizeof(char *));
	if (!node->str_options)
		return (NULL);
	node->str_options = cmd_str(tmp_token, node->str_options);
	node->next = NULL;
	return (node);
}

t_node	*nodizer_unit(t_token *token, t_data *data)
{
	t_token	*tmp_token;
	t_node	*node;

	tmp_token = token;
	node = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type_2 == COMMAND)
			node = make_cmd(token);
		token = token->next;
	}
	if (!node)
	{
		node = malloc(sizeof(t_node));
		if (!node)
			return (NULL);
		node->str_options = NULL;
		node->next = NULL;
	}
	node->heredoc = NULL;
	manage_heredoc(node, tmp_token, data);
	node->fd_in = init_in(tmp_token, data);
	node->fd_out = init_out(tmp_token);
	return (node);
}

t_token	*next_unit(t_token *token)
{
	while (token && token->type != PIPE)
		token = token->next;
	if (token && token->type == PIPE)
		return (token->next);
	else
		return (NULL);
}

t_node	*nodizer(t_token *token, t_data *data)
{
	t_node	*node;
	t_node	*tmp_node;
	t_node	*prev;

	prev = NULL;
	node = NULL;
	while (token)
	{
		node = nodizer_unit(token, data);
		node->data = data;
		node->prev = prev;
		prev = node;
		token = next_unit(token);
	}
	while (node && node->prev)
	{
		tmp_node = node;
		node = node->prev;
		node->next = tmp_node;
	}
	return (node);
}
