/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:24:43 by cgermain          #+#    #+#             */
/*   Updated: 2023/12/19 17:03:16 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_data(char **env2, t_data *data)
{
	data->last_error = 0;
	data->malloc_error = 0;
	data->is_path = 1;
	data->envp = tab_to_list(env2);
	if (!data->envp)
	{
		free_data(data);
		free_env(env2);
		ft_putstr_fd("Error : malloc failed\n", 2);
		return (0);
	}
	data->path = ft_strdup("/bin/");
	if (!data->path)
	{
		free_data(data);
		free_env(env2);
		ft_putstr_fd("Error : malloc failed\n", 2);
		return (0);
	}
	return (1);
}

int	exit_error(t_data *data)
{
	ft_putstr_fd("Error : env malloc failed\n", 2);
	free(data);
	return (1);
}

void	close_and_free(t_data *data, int in, int out, char **env2)
{
	close(in);
	close(out);
	free_env(env2);
	free_data(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	**env2;
	int		in;
	int		out;

	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	env2 = init_env(envp, data);
	if (!env2)
		return (exit_error(data));
	if (!init_data(env2, data))
		return (1);
	data->envlen = ft_lstsize(data->envp);
	signal_loop(data);
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (argc == 1)
		prompt(data, in, out);
	else
		ft_putstr_fd("Error : launch without args\n", 2);
	close_and_free(data, in, out, env2);
}
