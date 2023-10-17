/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:31:31 by cgermain          #+#    #+#             */
/*   Updated: 2023/09/25 11:13:36 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *fill_command(char *commande, char *env_value, char *str, size_t i, size_t k)
{
    size_t j;

    j = 0;
    while (j < k)
	{
		str[j] = commande[j];
		j++;
	}
	while(j < (ft_strlen(env_value) + k))
	{
		str[j] = env_value[j - k];
		j++;
	}
	while(commande[i])
	{
		str[j] = commande[i];
		i++;
		j++;
	}
	str[j] = '\0';
    return (str);
}

char *new_command(char *commande, char *env_value, int i)
{
	size_t	k;
	char *str;
	
	k = i;
    if (!env_value)
            return (commande);
	while(commande[i] != ' ' && commande[i] != '\0' && commande[i] != '"')
		i++;
	str = malloc(sizeof(char) * ((ft_strlen(commande) - (i-k)) + ft_strlen(env_value)));
	if(!str)
		return (NULL);
	str = fill_command(commande, env_value, str, i, k);
	free(commande);
	return (str);
}

int env_value_quote(int i, char **commande, t_list *envp)
{	
	int	j;

	i++;
	while((*commande)[i] && (*commande)[i] != '"')
	{
		if ((*commande)[i] == '$')
		{
			i++;
			j = i;
			while ((*commande)[i] && (*commande)[i] != ' ' && (*commande)[i] != '"')
				i++;
			if ((*commande)[i] == '"')
				(*commande) = new_command((*commande), get_env_value(envp, ft_strdup_c(&(*commande)[j], '"')), j - 1);
			else
				(*commande) = new_command((*commande), get_env_value(envp, ft_strdup_c(&(*commande)[j], ' ')), j - 1);
		}
		i++;
	}
	if((*commande)[i] == '"')
		i++;
	return (i);
}

int	env_value_dollar(int i, char **commande, t_list *envp)
{
	i++;
	(*commande) = new_command((*commande), get_env_value(envp, ft_strdup_c(&(*commande)[i], ' ')), i - 1);
	while ((*commande)[i] && (*commande)[i] != ' ')
		i++;
	return (i);
}


char *env_value_checker(char *commande, t_list *envp)
{
	int i;

	i = 0;
	while (commande[i])
	{
		if (commande[i] == 39)
		{
			i++;
			while(commande[i] && commande[i] != 39)
				i++;
			if (commande[i] == 39)
			i++;
		}
		else if (commande[i] == '"')
		{
			i = env_value_quote(i, &commande, envp);
		}
		else if (commande[i] == '$')
			i = env_value_dollar(i, &commande, envp);
		else 
			i++;
	}
	return (commande);
}