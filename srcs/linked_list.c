/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rshay <rshay@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/09/30 18:04:39 by rshay			 #+#	#+#			 */
/*   Updated: 2023/12/18 22:48:58 by rshay            ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

t_list	*tab_to_list(char **tab)
{
	int		i;
	t_list	*first;
	t_list	*new;

	first = ft_lstnew(ft_strdup(tab[0]));
	i = 1;
	while (tab[i])
	{
		new = ft_lstnew(ft_strdup(tab[i]));
		ft_lstadd_back(&first, new);
		i++;
	}
	return (first);
}

char	**list_to_tab(t_list *env)
{
	char	**tab;
	t_list	*current;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	current = env;
	tab = malloc((ft_lstsize(env) + 1) * sizeof(char *));
	while (current)
	{
		tab[i] = ft_strdup(current->content);
		current = current->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

t_list	*ft_lstdupnew(char *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	return (new);
}
