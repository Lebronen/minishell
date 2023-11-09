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
	result = malloc(sizeof(char) * 6 + ft_strlen(number) + 1);
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
		if (!ft_strncmp(envp->content, "SHLVL=", 6))
		{
			str = manage_shlvl(envp->content);
			envp->content = str;
			return ;
		}
		envp = envp->next;
	}

}

