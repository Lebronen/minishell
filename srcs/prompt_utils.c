/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <cgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:27:27 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/28 10:27:32 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_command(char *commande)
{
	if (!commande)
	{
		ft_putstr_fd("exit\n", 1);
		return (1);
	}
	return (0);
}

void	init_node(char	**commande, t_token **token,
							t_node **node, t_data *data)
{
	*node = NULL;
	*commande = env_value_checker(*commande, data);
	*token = lexer(*commande, data);
	*node = nodizer(*token, data);
}

char	*manage_error_cmd(char *commande, char *cwd)
{
	free(commande);
	return (readline(cwd));
}
