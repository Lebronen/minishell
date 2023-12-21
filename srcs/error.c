/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:49:21 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/29 19:11:39 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_ambig(char *commande, t_data *data)
{
	int	i;

	i = 0;
	while (commande && commande[i])
	{
		if (commande[i] == '<' || commande[i] == '>')
		{
			i ++;
			if (commande[i] && commande[i] == '$')
			{
				while (commande[i] && commande [i] != ' ' && commande[i] != '|')
				{
					write(2, &commande[i], 1);
					i++;
				}
				print_error(1, NULL, " : ambiguous redirect\n", data);
				return (1);
			}
		}
		if (commande[i])
			i++;
	}
	return (0);
}

int	error_cmd4(char *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '>')
		{
			if (cmd[i + 1] && cmd[i + 1] == '<')
				return (print_error(2, NULL, "Syntax error\n", data));
			else if (cmd[i + 1] && cmd[i + 1] == '>')
				if (cmd[i + 2] && (cmd[i + 2] == '>' || cmd[i + 2] == '<'))
					return (print_error(2, NULL, "Syntax error\n", data));
		}
		else if (cmd[i] == '<')
		{
			if (cmd[i + 1] && cmd[i + 1] == '>')
				return (print_error(2, NULL, "Syntax error\n", data));
			else if (cmd[i + 1] && cmd[i + 1] == '<')
				if (cmd[i + 2] && (cmd[i + 2] == '>' || cmd[i + 2] == '<'))
					return (print_error(2, NULL, "Syntax error\n", data));
		}
		i++;
	}
	return (0);
}

int	error_cmd3(char *commande, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (commande[i])
	{
		if (commande[i] == '|')
		{
			j = i - 1;
			while (commande[j] && (commande[j] == ' ' || commande[j] == 9))
				j--;
			if (commande[j] == '<' || commande[j] == '>' || commande[j] == '|')
				return (print_error(2, NULL, "Syntax error\n", data));
		}
		i++;
	}
	return (error_cmd4(commande, data));
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
		return (print_error(2, NULL, "Syntax error\n", data));
	}
	return (error_cmd3(commande, data));
}

int	error_cmd(char *commande, t_data *data)
{
	int		i;

	i = 0;
	if (!commande)
		return (1);
	if (!commande[i] || error_ambig(commande, data))
		return (1);
	while (commande[i] == ' ' || commande[i] == 9 || commande[i] == 11)
		i++;
	if (error_cmd2(commande, i, data))
		return (1);
	return (syntax_error(data, commande, i));
}
