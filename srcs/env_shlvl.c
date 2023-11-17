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

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	manage_shlvl(char *env, char **result, int j)
{
	int		nb;
	int		i;
	char	*number;

	i = 0;
	nb = ft_atoi(&env[6]);
	nb++;
	number = ft_itoa(nb);
	result[j] = malloc(sizeof(char) * (7 + ft_strlen(number)));
	if (!result)
		return ;
	while (i < 6)
	{
		result[j][i] = env[i];
		i++;
	}
	while (number[i - 6])
	{
		result[j][i] = number[i - 6];
		i++;
	}
	free(number);
	result[j][i] = '\0';
}
/*
char **create_envp(void)
{
	
}*/