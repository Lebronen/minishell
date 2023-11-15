/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:42:53 by rshay             #+#    #+#             */
/*   Updated: 2023/11/03 17:35:53 by rshay            ###   ########.fr       */
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


void    execute(char **commande, t_data *data)
{
    char    *path;
	char	**tab;
    
		tab = list_to_tab(data->envp);
        if (is_slash(commande[0]))
            path = commande[0];
        else
            path = find_path(commande[0], tab);
        if (!path || execve(path, commande, tab) == -1)
	    {
			error(data);
		}
}

void	process(t_node *node, t_data *data)
{
	pid_t	pid;
	int		status;
	
	if (node->fd_in == STDIN_FILENO && node->fd_out == STDOUT_FILENO)
	{
		
		pid = fork();
		if (pid == 0)
			execute(node->str_options, data);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
		}
		else
		{
			data->last_error = 666;
			perror("fork");
		}
	}
	else
		ft_redirect(node, data);
}