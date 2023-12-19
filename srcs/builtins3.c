/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:58:26 by rshay             #+#    #+#             */
/*   Updated: 2023/12/19 15:47:12 by rshay            ###   ########.fr       */
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
