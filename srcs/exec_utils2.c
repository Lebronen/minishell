/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:51:54 by rshay             #+#    #+#             */
/*   Updated: 2023/12/05 15:49:26 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execloop(t_node *node)
{
	int	tube1[2];
	int	tube2[2];
	int	in;
	int	out;
	int	nb;

	tube1[0] = 0;
	tube1[1] = 1;
	tube2[0] = 0;
	tube2[1] = 1;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	nb = nb_pipes(node);
	ft_pipe(node, tube1, tube2, nb);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
}
