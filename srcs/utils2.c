/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:06:59 by lebronen          #+#    #+#             */
/*   Updated: 2023/10/14 16:58:20 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	exit(EXIT_SUCCESS);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0644);
	if (file == -1)
		error();
	return (file);
}

void	del(void *content)
{
	content = NULL;
	free(content);
}

int	ft_index(char *commande, char c)
{
	int	i;

	i = 0;
	while (commande[i] != c)
		i++;
	return (i);
}
