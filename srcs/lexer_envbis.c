/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_envbis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:55:34 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/13 16:55:35 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_value_quote1(int i, char**commande, t_list *envp)
{
	int		j;
	char	*str;
	char	*str1;

	i++;
	j = i;
	while ((*commande)[i] &&
		(*commande)[i] != ' ' && (*commande)[i] != '"')
		i++;
	if ((*commande)[i] == '"')
		str1 = ft_strdup_c2(&(*commande)[j], '"');
	else
		str1 = ft_strdup_c2(&(*commande)[j], ' ');
	str = get_env_value(envp, str1);
	(*commande) = new_command((*commande), str, j - 1);
	free(str);
	free(str1);
	return (i);
}

int	env_value_quote2(int i, char **commande)
{
	int		j;
	int		k;
	char	*str1;

	k = 0;
	i++;
	if ((*commande)[i] == '$')
		k = 1;
	j = i;
	while ((*commande)[i] &&
		(*commande)[i] != ' ' && (*commande)[i] != '"')
			i++;
	if ((*commande)[i] == '"')
		str1 = ft_strdup_c(&(*commande)[j], '"');
	else
		str1 = ft_strdup_c(&(*commande)[j], ' ');
	(*commande) = new_command((*commande), str1, j - k);
	free(str1);
	return (i);
}

int	env_value_quote(int i, char **commande, t_list *envp)
{	
	while ((*commande)[i] && (*commande)[i] != '"')
	{
		if ((*commande)[i] == '$')
			i = env_value_quote1(i, commande, envp);
		else if ((*commande)[i] == 92)
			i = env_value_quote2(i, commande);
		i++;
	}
	if ((*commande)[i] == '"')
		i++;
	return (i);
}
