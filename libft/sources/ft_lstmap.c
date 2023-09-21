/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vegret <victor.egret.pro@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:35:45 by vegret            #+#    #+#             */
/*   Updated: 2022/09/05 23:35:45 by vegret           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*new;

	if (!f || !del)
		return (NULL);
	mapped = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			while (mapped)
			{
				new = mapped->next;
				(*del)(mapped->content);
				free(mapped);
				mapped = new;
			}
			return (NULL);
		}
		ft_lstadd_back(&mapped, new);
		lst = lst->next;
	}
	return (mapped);
}
