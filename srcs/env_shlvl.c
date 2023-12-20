/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:53:44 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/22 18:57:15 by lebronen         ###   ########.fr       */
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

void	fill_shlvl(char **result, char *env, char *number)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		(*result)[i] = env[i];
		i++;
	}
	while (number[i - 6])
	{
		(*result)[i] = number[i - 6];
		i++;
	}
	free (number);
	(*result)[i] = '\0';
}

int	manage_shlvl(char *env, char **result, int j)
{
	int		nb;
	char	*number;

	nb = ft_atoi(&env[6]) + 1;
	number = ft_itoa(nb);
	if (!number)
	{
		result[j] = NULL;
		return (0);
	}
	result[j] = malloc(sizeof(char) * (7 + ft_strlen(number)));
	if (!result[j])
	{
		free(number);
		return (0);
	}
	fill_shlvl(&result[j], env, number);
	return (1);
}

char	*manage_pwd(void)
{
	char	str[256];
	char	cwd[256];

	str[0] = 'P';
	str[1] = 'W';
	str[2] = 'D';
	str[3] = '=';
	str[4] = '\0';
	getcwd(cwd, sizeof(cwd));
	ft_strlcat(str, cwd, 256);
	return (ft_strdup(str));
}

char	**create_envp(t_data *data)
{
	char	**envp;

	data->is_env = 0;
	envp = malloc(sizeof(char *) * 3);
	if (!envp)
		return (NULL);
	envp[0] = manage_pwd();
	if (!envp[0])
	{
		free_env(envp);
		return (NULL);
	}
	envp[1] = ft_strdup("SHLVL=1");
	if (!envp[1])
	{
		free_env(envp);
		return (NULL);
	}
	envp[2] = NULL;
	return (envp);
}
