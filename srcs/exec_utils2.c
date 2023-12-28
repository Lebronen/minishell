/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:51:54 by rshay             #+#    #+#             */
/*   Updated: 2023/12/28 17:42:55 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_redir(t_node *node)
{
	t_node	*tmp;
	int		redir;

	tmp = node;
	redir = 0;
	while (tmp)
	{
		if (tmp->fd_out != STDOUT_FILENO)
			redir++;
		if (tmp->fd_in != STDIN_FILENO)
			redir++;
		tmp = tmp->next;
	}
	return (redir);
}

void	ft_closing_fd(t_node *node)
{
	int	i;
	int	fds;

	i = 0;
	fds = 0;
	while (i < nb_pipes(node) + 1)
	{
		fds += fds + 1;
		i++;
	}
	i = 0;
	while (i <= fds + nb_redir(node))
	{
		close(i + 5);
		i++;
	}
}

void	close_on_exit(t_node *node, int in, int out)
{
	t_node	*tmp;

	tmp = node;
	while (tmp)
	{
		if (tmp->fd_in != STDIN_FILENO && tmp->fd_in != -2)
			close(tmp->fd_in);
		if (tmp->fd_out != STDOUT_FILENO)
			close(tmp->fd_out);
		tmp = tmp->next;
	}
	close(in);
	close(out);
	ft_closing_fd(node);
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
	if (!node->str_options || !node->str_options[0])
		return ;
	if (node->str_options
		&& !ft_strcmp("exit", node->str_options[0]) && !node->next)
		close_on_exit(node, in, out);
	ft_pipe(node, tube1, tube2, nb);
	close_on_exit(node, in, out);
}
