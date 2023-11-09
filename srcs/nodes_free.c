/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <cgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:04:31 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/19 15:04:34 by cgermain         ###   ########.fr       */
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
		if (node->heredoc)
			free_heredoc(node);
		temp_node = node->next;
		if (node)
			free(node);
		node = temp_node;
	}
}
