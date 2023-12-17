/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rshay <rshay@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/12/05 16:48:55 by rshay			 #+#	#+#			 */
/*   Updated: 2023/12/05 16:57:56 by rshay            ###   ########.fr       */
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
