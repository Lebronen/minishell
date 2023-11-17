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

char	*manage_shlvl(char *env, char *result)
{
	int	nb;
	int	i;
	char *number;

	i = 0;
	nb = ft_atoi(&env[6]);
	nb++;
	number = ft_itoa(nb);
	free(result);
	result = malloc(sizeof(char) * (7 + ft_strlen(number)));
	if (!result)
		return (NULL);
	while (i < 6)
	{
		result[i] = env[i];
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