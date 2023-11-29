/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:49:21 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/24 12:49:30 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_ambig(char *commande, t_data *data)
{
	int	i;

	i = 0;
	while (commande[i])
	{
		if (commande[i] == '<' || commande[i] == '>')
		{
			i ++;
			if (commande[i] == '$')
			{
				while (commande[i] && commande [i] != ' ' && commande[i] != '|')
				{
					write(2, &commande[i], 1);
					i++;
				}
				print_error(1, 2, " : ambiguous redirect\n", data);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	error_cmd2(char *commande, int i, t_data *data)
{
	if (commande[i] == '\0'
		|| (commande[i] == ':' && commande[i + 1] == '\0'))
	{
		data->last_error = 0;
		return (1);
	}
	else if (commande[i] == '!' && commande[i + 1] == '\0')
	{
		data->last_error = 1;
		return (1);
	}
	else if (commande[i] == '|')
	{
		return (print_error(2, 2, "Syntax error\n", data));
	}
	return (0);
}

int	error_cmd(char *commande, t_data *data)
{
	int		i;
	char	c;
	int		quotes;

	quotes = 0;
	i = 0;
	if (!commande[i])
		return (1);
	while (commande[i] == ' ' || commande[i] == 9 || commande[i] == 11)
		i++;
	if (error_cmd2(commande, i, data))
		return (1);
	while (commande[i])
	{
		if (commande[i] != ' ' || commande[i] != 9)
			c = commande[i];
		if (commande[i] == '"' || commande[i] == '\'')
			quotes++;
		i++;
	}
	if (c == '|' || c == '>' || c == '<' || quotes % 2 != 0)
		return (print_error(2, "", "Syntax error\n", data));
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
	ft_putstr_fd("'", 2);
	ft_putstr_fd("':", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(str, 2);
	return (1);
}
