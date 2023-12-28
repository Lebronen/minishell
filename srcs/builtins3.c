/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:58:26 by rshay             #+#    #+#             */
/*   Updated: 2023/12/28 19:35:55 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_export(t_data *data)
{
	t_list	*current;

	if (!data->envp)
	{
		ft_printf("env error\n");
		return (127);
	}
	current = data->envp;
	while (current)
	{
		ft_printf("export %s\n", current->content);
		current = current->next;
	}
	return (0);
}

void	free_first(t_list **lst)
{
	t_list	*next;

	next = (*lst)->next;
	free((*lst)->content);
	free(*lst);
	*lst = next;
}

void	remove_loop(t_data *data, char *commande)
{
	t_list	*current;
	t_list	*next;

	current = data->envp;
	while (current && current ->next)
	{
		if (!ft_strlencmp(current->next->content,
				commande, ft_index(current->next->content, '=')))
		{
			next = current->next->next;
			free(current->next->content);
			free(current->next);
			current->next = next;
		}
		current = current->next;
	}
}

int	is_n_good(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
