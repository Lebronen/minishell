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

char	*fill_command(char *commande, char *env_value, char *str, size_t k)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = boost_i(commande, k);
	while (j < k)
	{
		str[j] = commande[j];
		j++;
	}
	while (j < (ft_strlen(env_value) + k))
	{
		str[j] = env_value[j - k];
		j++;
	}
	while (commande[i])
	{
		str[j] = commande[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*new_command(char *commande, char *env_value, int i)
{
	size_t	k;
	char	*str;

	k = i;
	if (!env_value)
		return (commande);
	while (commande[i] != ' ' && commande[i] != '\0' && commande[i] != '"'
		&& commande[i] != '$' && commande[i] != 39)
		i++;
	str = malloc(sizeof(char)
			* ((ft_strlen(commande) - (i - k)) + ft_strlen(env_value) + 1));
	if (!str)
		return (NULL);
	str = fill_command(commande, env_value, str, k);
	free(commande);
	return (str);
}

int	env_value_dollar(int i, char **commande, t_data *data)
{
	char	*str;
	char	*str1;

	str1 = NULL;
	if ((*commande)[i] == '?')
		str = ft_itoa(data->last_error);
	else
	{
		str1 = ft_strdup_c3(&(*commande)[i], '$');
		if (!str1)
		{
			data->malloc_error = 1;
			return (i++);
		}
		str = get_env_value(data->envp, str1);
	}
	(*commande) = new_command((*commande), str, i - 1);
	while ((*commande)[i] && (*commande)[i] != ' '
		&& (*commande)[i] != '$' && (*commande)[i] != '"')
		i++;
	if (str)
		free(str);
	if (str1)
		free(str1);
	return (i);
}

char	*error_env_value(char *commande, t_data *data)
{
	if (data->malloc_error != 0)
	{
		free(commande);
		return (NULL);
	}
	else
		return (commande);
}

char	*env_value_checker(char *commande, t_data *data)
{
	int	i;

	i = 0;
	if (g_sig_handle == SIGINT)
			data->last_error = 130;
	if (!commande)
		return (NULL);
	while (commande[i])
	{
		i++;
		if (commande[i - 1] == '$')
			i = env_value_dollar(i, &commande, data);
		else if (commande[i - 1] == 39)
		{
			while (commande[i] && commande[i] != 39)
				i++;
			if (commande[i] == 39)
			i++;
		}
		else if (commande[i - 1] == '"')
			i = env_value_quote(i, &commande, data);
	}
	return (error_env_value(commande, data));
}
