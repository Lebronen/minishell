/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:31:31 by cgermain          #+#    #+#             */
/*   Updated: 2023/09/21 16:20:13 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**fill_env(char **envp, char **result)
{
	int	i;
	int	j;

	j = 0;
	while (envp[j])
	{
		i = 0;
		while (envp[j][i])
		{
			result[j][i] = envp[j][i];
			i++;
		}
		result[j][i] = '\0';
		j++;
	}
	j--;
	envp[j][i] = '\0';
	return (result);
}

char	**init_env(char **envp)
{
	char	**result;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (result == NULL)
		return (NULL);
	i--;
	while (i >= 0)
	{
		result[i] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char *));
		if (!result[i])
			return (free_array(result));
		i--;
	}
	return (fill_env(envp, result));
}
