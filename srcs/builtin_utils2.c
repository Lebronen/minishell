/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rshay <rshay@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/12/05 16:48:55 by rshay			 #+#	#+#			 */
/*   Updated: 2023/12/28 19:29:39 by rshay            ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	loop_unset(char **commande, t_data *data)
{
	int	i;

	i = 1;
	while (commande[i])
	{
		data->last_error = unset(commande[i], data);
		i++;
	}
}

int	ft_strlencmp(char *s1, char *s2, int ind)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	while (s2[j] && s2[j] != '=')
		j++;
	if (i != j)
		return (1);
	return (ft_strncmp(s1, s2, ind));
}
