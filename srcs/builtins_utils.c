/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lebronen <lebronen@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/10/28 17:06:05 by rshay			 #+#	#+#			 */
/*   Updated: 2023/11/29 17:10:11 by rshay            ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

int	is_also_builtin(char **commande, t_data *data)
{
	if (!ft_strcmp(commande[0], "echo"))
	{
		if (!commande[1])
			return (1);
		if (!ft_strcmp(commande[1], "-n"))
		{
			if (commande[2])
				data->last_error = echo(commande[2], 1, 1);
		}
		else
			data->last_error = echo(commande[1], 0, 1);
		return (1);
	}
	else if (!ft_strcmp(commande[0], "unset"))
	{
		data->last_error = unset(commande[1], data->envp);
		return (1);
	}
	return (0);
}

int	is_builtin_exec(char **commande, t_data *data)
{
	if (!ft_strcmp(commande[0], "cd"))
	{
		cd(commande[1], data->envp);
		return (1);
	}
	else if (!ft_strcmp(commande[0], "pwd"))
	{
		data->last_error = pwd();
		return (1);
	}
	else if (!ft_strcmp(commande[0], "env"))
	{
		data->last_error = env(data);
		return (1);
	}
	else if (!ft_strcmp(commande[0], "export"))
	{
		data->last_error = export(commande[1], data->envp);
		return (1);
	}
	return (is_also_builtin(commande, data));
}

int	is_only_builtin(char **commande)
{
	if (!ft_strcmp(commande[0], "cd"))
		return (1);
	else if (!ft_strcmp(commande[0], "export"))
		return (1);
	else if (!ft_strcmp(commande[0], "unset"))
		return (1);
	return (0);
}

int	is_builtin(char **commande)
{
	if (!strcmp(commande[0], "cd") || !strcmp(commande[0], "pwd"))
		return (1);
	if (!strcmp(commande[0], "pwd") || !strcmp(commande[0], "env"))
		return (1);
	if (!strcmp(commande[0], "export") || !strcmp(commande[0], "unset"))
		return (1);
	return (0);
}
