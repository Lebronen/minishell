/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:14:32 by lebronen          #+#    #+#             */
/*   Updated: 2023/12/19 17:04:36 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	error(t_data *data)
{
	perror("Error");
	data->last_error = 666;
	exit(EXIT_FAILURE);
}

int	is_slash(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	execute(char **commande, t_data *data)
{
	char	*path;
	char	**tab;

	path = NULL;
	tab = list_to_tab(data->envp);
	if (is_slash(commande[0]))
		path = commande[0];
	else if (!data->is_env)
	{
		path = ft_strdup(data->path);
		ft_strlcat(path, commande[0], ft_strlen(commande[0]) + 6);
	}
	else if (data->is_path)
		path = find_path(commande[0], tab);
	if (!path || execve(path, commande, tab) == -1)
	{
		if (!path)
		{
			print_error(127, commande[0], " Command not found\n", data);
		}
		else if (commande[0][0] == '/')
			print_error(127, commande[0], " No such file or directory\n", data);
		exit(127);
	}
}

void	process(t_node *node, t_data *data, int in, int out)
{
	if (node->str_options && node->str_options[0]
		&& !ft_strncmp(node->str_options[0], "./minishell", 12))
		signal(SIGINT, SIG_IGN);
	else
	{
		signal(SIGINT, signal_handler_exec);
		signal(SIGQUIT, signal_handler_exec);
	}
	execloop(node, in, out);
	if (g_sig_handle == SIGINT)
		data->last_error = 130;
	if (g_sig_handle == SIGQUIT)
		data->last_error = 131;
	g_sig_handle = 0;
}
