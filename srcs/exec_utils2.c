/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:51:54 by rshay             #+#    #+#             */
/*   Updated: 2023/12/28 11:35:55 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_on_exit(t_node *node, int in, int out)
{
	while (node)
	{
		if (node->fd_in != STDIN_FILENO && node->fd_in != -2)
			close(node->fd_in);
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		node = node->next;
	}
	close(in);
	close(out);
}

void	execloop(t_node *node, int in, int out)
{
	int	tube1[2];
	int	tube2[2];
	int	nb;

	tube1[0] = -1;
	tube1[1] = -1;
	tube2[0] = -1;
	tube2[1] = -1;
	nb = nb_pipes(node);
	if (node->str_options
		&& !ft_strcmp("exit", node->str_options[0]) && !node->next)
		close_on_exit(node, in, out);
	ft_pipe(node, tube1, tube2, nb);
	close_on_exit(node, in, out);
}
