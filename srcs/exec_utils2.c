/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:51:54 by rshay             #+#    #+#             */
/*   Updated: 2023/11/29 16:55:25 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execloop(t_node *node)
{
	int	tube1[2];
	int	tube2[2];
	int	nb;

	nb = nb_pipes(node);
	ft_pipe(node, tube1, tube2, nb);
}
