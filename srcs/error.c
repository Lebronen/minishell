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


int	error_ambig(char *commande)
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
				write(2, " : ambiguous redirect\n", 22);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	error_cmd(char *commande)
{
	int		i;
	char	c;
	char	d;
	int		quotes;

	quotes = 0;
	i = 0;
	if (!commande[i])
		return (1);
	while (commande[i] == ' ')
		i++;
	d = commande[i];
	while (commande[i])
	{
		if (commande[i] != ' ')
			c = commande[i];
		if (commande[i] == '"' || commande[i] == '\'')
			quotes++;
		i++;
	}
	if (d == '|' ||  c == '|' || c == '>' || c == '<')
	{
		write(2, "syntax error\n", 13);
		return (1);
	}
	if (quotes % 2 != 0)
	{
		write(2, "unclosed quotes\n", 16);
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