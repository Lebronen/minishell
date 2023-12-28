/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lebronen <lebronen@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/10/28 17:06:05 by rshay			 #+#	#+#			 */
/*   Updated: 2023/11/29 18:28:04 by rshay            ###   ########.fr       */
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
	return (*s1 != *s2);
}

void	is_also_builtin(char **commande, t_data *data)
{
	if (!ft_strcmp(commande[0], "echo"))
	{
		if (!commande[1])
			write(1, "\n", 1);
		else if (!ft_strncmp(commande[1], "-n", 2))
			data->last_error = n_parsing(commande);
		else
			data->last_error = echo(commande, 1, 1);
	}
	else if (!ft_strcmp(commande[0], "unset"))
		loop_unset(commande, data);
}

void	is_builtin_exec(char **commande, t_data *data)
{
	if (!ft_strcmp(commande[0], "cd"))
		data->last_error = cd(commande[1], data);
	else if (!ft_strcmp(commande[0], "pwd"))
		data->last_error = pwd();
	else if (!ft_strcmp(commande[0], "env"))
		data->last_error = env(data);
	else if (!ft_strcmp(commande[0], "export"))
		loop_export(commande, data);
	else if (!ft_strcmp(commande[0], "exit"))
		ft_exit(commande, data);
	else
		is_also_builtin(commande, data);
}

int	is_only_builtin(char **commande)
{
	if (!ft_strcmp(commande[0], "cd"))
		return (1);
	else if (!ft_strcmp(commande[0], "export"))
		return (1);
	else if (!ft_strcmp(commande[0], "unset"))
		return (1);
	else if (!strcmp(commande[0], "exit"))
		return (1);
	else
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
	if (!strcmp(commande[0], "exit") || !strcmp(commande[0], "echo"))
		return (1);
	else
		return (0);
}
