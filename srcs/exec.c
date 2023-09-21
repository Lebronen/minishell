/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:42:53 by rshay             #+#    #+#             */
/*   Updated: 2023/09/19 16:05:19 by lebronen         ###   ########.fr       */
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


void    execute(char *commande, char **envp)
{
    char    **cmd;
    char    *path;
    int     i;
    
    
        cmd = ft_split(commande, ' ');
        if (is_slash(cmd[0]))
            path = cmd[0];
        else
            path = find_path(cmd[0], envp);
        if (!path || execve(path, cmd, envp) == -1)
	    {  
            i = -1;
            while (cmd[++i])
                free(cmd[i]);
            free(cmd);
            error();
		}
}

void	process(char *commande, char **envp)
{
	int		nb_pipes;
	int		nb_redout;
	int		nb_redin;
	pid_t   pid;
	int		status;

	nb_pipes = nb_str(commande, '|');
	nb_redout = nb_str(commande, '>');
	nb_redin = nb_str(commande, '<');
	if (!nb_pipes && !nb_redout && !nb_redin)
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
	else if (nb_pipes)
		ft_pipe(commande, envp);
	else if (nb_redout)
		ft_redirect_out(commande, envp);
	else
		ft_redirect_in(commande, envp);
}