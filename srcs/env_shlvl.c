/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:53:44 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/03 15:53:50 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *manage_shlvl(char *str)
{
	int	nb;
	int	i;
	char *result;
	char *number;

	i = 0;
	nb = ft_atoi(&str[6]);
	nb++;
	number = ft_itoa(nb);
	result = malloc(sizeof(char) * 7 + ft_strlen(number));
	if (!result)
		return (NULL);
	while (i < 6)
	{
		result[i] = str[i];
		i++;
	}
	while (number[i - 6])
	{
		result[i] = number[i - 6];
		i++;
	}
	free(number);
	result[i] = '\0';
	return (result);
}


void	set_shlvl(t_list *envp)
{
	char *str;

	while (envp)
	{
		t_list *envp_prev;
		t_list *envp_next;
		t_list	*new;

		if (envp->next && !ft_strncmp(envp->next->content, "SHLVL=", 6))
		{	
			envp_prev = envp;
			envp = envp->next;
			envp_next = envp->next;
			str = manage_shlvl(envp->content);
			free(envp);
			new = ft_lstnew(str);
			free(str);
			envp_prev->next = new;
			new->next = envp_next;
			return ;
		}
		envp = envp->next;
	}

}

