/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <cgermain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:02:17 by cgermain          #+#    #+#             */
/*   Updated: 2023/10/19 15:02:25 by cgermain         ###   ########.fr       */
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
		if (!ft_strncmp(envp[j], "SHLVL=", 6))
		{
			manage_shlvl(envp[j], result, j);
			j++;
		}
		while (envp[j][i])
		{
			result[j][i] = envp[j][i];
			i++;
		}
		result[j][i] = '\0';
		j++;
	}
	result[j] = NULL;
	return (result);
}

char	**init_env(char **envp)
{
	char	**result;
	int		i;

	i = 0;
	if (!envp[0])
		return(create_envp());
	while (envp[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (result == NULL)
		return (NULL);
	i--;
	while (i >= 0)
	{
		if (envp && strncmp(envp[i], "SHLVL=", 6))
		{
			result[i] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
			if (!result[i])
				return (free_array(result));
		}
		i--;
	}
	return (fill_env(envp, result));
}

static int	compare_words(char *word1, char *word2)
{
	size_t	i;

	i = 0;
	while (word1[i] == word2[i] && word1 && word2)
		i++;
	if (i == ft_strlen(word2) && word1[i] == '=')
		return (1);
	return (0);
}

char	*get_env_value(t_list *envp, char *name)
{
	int		j;

	j = 0;
	while (envp)
	{
		if (compare_words(envp->content, name))
		{
			j = ft_strlen(name) + 1;
			return (ft_strdup((&envp->content)[j]));
		}
		envp = envp->next;
	}
	return (NULL);
}
