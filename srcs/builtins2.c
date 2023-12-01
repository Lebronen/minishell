/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:02:37 by rshay             #+#    #+#             */
/*   Updated: 2023/12/01 15:10:45 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char *commande, t_list *envp)
{
	t_list	*current;
	t_list	*new;
	int		here;

	here = 0;
	current = envp;
	while (current)
	{
		if (!ft_strncmp(current->content, commande, ft_index(commande, '=')))
		{
			current->content = ft_strdup(commande);
			here = 1;
		}
		current = current->next;
	}
	if (!here)
	{
		new = ft_lstdupnew(commande);
		ft_lstadd_back(&envp, new);
		if (!ft_strncmp(commande, "PATH", 4))
			return (1);
	}
	return (0);
}

int	unset(char *commande, t_list *envp)
{
	t_list	*current;
	t_list	*next;

	current = envp;
	while (current && current ->next)
	{
		if (!ft_strncmp(current->next->content, commande, ft_strlen(commande)))
		{
			next = current->next->next;
			ft_lstdelone(current->next, &del);
			current->next = next;
		}
		current = current->next;
	}
	return (0);
}
