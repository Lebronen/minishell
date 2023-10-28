/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:42:53 by rshay             #+#    #+#             */
/*   Updated: 2023/10/28 17:29:30 by rshay            ###   ########.fr       */
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
	
	if (!is_builtin(node->str_options))
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
	/*
	int		nb_pipes;
	int		nb_redout;
	int		nb_redin;
	pid_t   pid;
	int		status;

	nb_pipes = nb_str(commande, '|');
	nb_redout = nb_str(commande, '>');
	nb_redin = nb_str(commande, '<');
	if (nb_pipes)
		ft_pipe(commande, envp);
	else if (nb_redout == 1)
		ft_redirect_out(commande, envp);
	else if (nb_redout == 2)
		ft_double(commande, envp);
	else if (!ft_strncmp("cd", commande, 2))
		cd(commande + 3);
	else if (!ft_strncmp("pwd", commande, 3))
		pwd();
	else if (!ft_strncmp("env", commande, 3))
		env(envp);
	else if (!ft_strncmp("echo", commande, 4))
	{
		if (! ft_strncmp("-n", commande + 5, 2))
			echo(commande + 8, 1, 1);
		else
			echo(commande + 5, 0, 1);
	}
	
	else if (!ft_strncmp("export", commande, 6))
		export(commande + 7, envp);
	
	else if (!ft_strncmp("unset", commande, 5))
		unset(commande + 6, envp);
	
	else if (nb_redin == 1)
		ft_redirect_in(commande, envp);
	else if (nb_redin == 2)
		ft_heredoc(commande, envp);
	else
	{
		pid = fork();
		if (pid == 0)
			execute(commande, envp);
		else if (pid > 0)
    	{
			waitpid(pid, &status, 0);
    	}
		else
			perror("fork");
	}
	*/
}