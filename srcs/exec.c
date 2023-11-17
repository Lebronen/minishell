/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:42:53 by rshay             #+#    #+#             */
/*   Updated: 2023/11/12 19:42:44 by lebronen         ###   ########.fr       */
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

void	error(void)
{
	perror("Error");
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


void    execute(char **commande, t_list *envp)
{
    char    *path;
	char	**tab;
    
		tab = list_to_tab(envp);
        if (is_slash(commande[0]))
            path = commande[0];
        else
            path = find_path(commande[0], tab);
        if (!path || execve(path, commande, tab) == -1)
	    {
            error();
		}
}

void	process(t_node *node, t_list *envp)
{
	pid_t	pid;
	int		status;
	
	if (nb_pipes(node) > 0)
		ft_pipe(node, envp);
	if (node->fd_in == STDIN_FILENO && node->fd_out == STDOUT_FILENO)
	{
		if (! is_builtin(node->str_options, envp))
		{
			
			pid = fork();
			if (pid == 0)
				execute(node->str_options, envp);
			else if (pid > 0)
			{
				waitpid(pid, &status, 0);
			}
			else
				perror("fork");
		}
	}
		else
			ft_redirect(node, envp);
}