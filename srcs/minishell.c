/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:24:43 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/14 12:24:46 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char 	**env2;

	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->last_error = 0;
	env2 = init_env(envp);
	data->envp = tab_to_list(env2);
	signal_loop(data);
	if (argc == 1)
	{
		prompt(data);
	}
	else
	{
		ft_putstr_fd("Error : launch without args", 2);
	}
	free_env(env2);
	free_data(data);
}
