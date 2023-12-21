/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:04:31 by cgermain          #+#    #+#             */
/*   Updated: 2023/12/19 15:01:27 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc(t_node *node)
{
	int	i;

	i = 0;
	while (node->heredoc && node->heredoc[i])
	{
		free(node->heredoc[i]);
		i++;
	}
	free(node->heredoc);
}

void	free_nodes(t_node *node)
{
	int		i;
	t_node	*temp_node;

	while (node)
	{
		i = 0;
		if (node->str_options)
		{
			while (node->str_options[i])
			{
				free(node->str_options[i]);
				i++;
			}
			free(node->str_options);
		}
		if (node->heredoc != NULL)
			free_heredoc(node);
		temp_node = node->next;
		if (node)
			free(node);
		node = temp_node;
	}
}

void	free_data(t_data *data)
{
	t_list	*temp_env;

	while (data->envp)
	{
		temp_env = data->envp->next;
		free(data->envp->content);
		free(data->envp);
		data->envp = temp_env;
	}
	free(data->envp);
	if (data->path)
		free(data->path);
	free(data);
}

t_node	*error_malloc_node(t_node *node)
{
	while (node && node->prev)
	{
		node = node->prev;
	}
	free_nodes(node);
	return (NULL);
}

t_node	*node_no_cmd(t_node *node)
{
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->str_options = NULL;
	node->next = NULL;
	return (node);
}
