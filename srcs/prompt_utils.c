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

int	init_node(char	**commande, t_token **token,
							t_node **node, t_data *data)
{
	*node = NULL;
	*commande = env_value_checker(*commande, data);
	if (!*commande)
	{
		ft_putstr_fd("Error : malloc failed\n", 2);
		return (0);
	}
	*token = lexer(*commande, data);
	if (!token)
	{
		ft_putstr_fd("Error : malloc failed\n", 2);
		return (0);
	}
	*node = nodizer(*token, data);
	if (!*node)
	{
		ft_putstr_fd("Error : malloc failed\n", 2);
		return (0);
	}
	data->last_error = 0;
	return (1);
}

char	*manage_error_cmd(char *commande)
{
	free(commande);
	return (readline("Minishell~$"));
}
