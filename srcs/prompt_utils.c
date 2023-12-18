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

int	input_error(char *str, t_data *data)
{
	write(2, "'", 1);
	ft_putstr_fd(str, 2);
	write(2, "' : No such file or directory\n", 30);
	data->last_error = 1;
	return (-1);
}

int	print_error(int error_num, char *name, char *str, t_data *data )
{
	data->last_error = error_num;
	if (name)
	{
		ft_putstr_fd("'", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("':", 2);
	}
	ft_putstr_fd(str, 2);
	return (1);
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
	return (1);
}

char	*manage_error_cmd(char *commande)
{
	free(commande);
	return (readline("Minishell~$"));
}
