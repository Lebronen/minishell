/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:42:53 by rshay             #+#    #+#             */
/*   Updated: 2023/11/26 19:07:04 by lebronen         ###   ########.fr       */
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
		{
            path = find_path(commande[0], tab);
			//else
			//{
				//path = malloc((5 + ft_strlen(commande[0])) * sizeof(char));
				//ft_memmove(path, "/bin/", 5);
				//ft_memmove(path + 5, commande[0], ft_strlen(path));
			//}
		}
        if (!path || execve(path, commande, tab) == -1)
	    {
			data->last_error = errno;
			error(data);
		}
}

void	process(t_node *node, t_data *data)
{
	pid_t	pid;
	int		status;
	int		fd;
	int		i;
	
	i= 0;
	if (!ft_strncmp(node->str_options[0], "./minishell", 12))
		signal(SIGINT, SIG_IGN);
	else
		signal(SIGINT, signal_handler_exec);

	if (nb_pipes(node) > 0)
		ft_pipe(node);
	else if (is_builtin(node->str_options, data))
		return;
	else if (node->fd_in == STDIN_FILENO && node->fd_out == STDOUT_FILENO)
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
			data->last_error = errno;
			perror("fork");
		}
	}
	else
	{
		if (node->fd_in == -2)
            {
                fd = open("/tmp/icidoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                    error(data);
                while (node->heredoc[i])
                {
                    ft_putstr_fd(node->heredoc[i], fd);
					write(fd, "\n", 1);
                    i++;
				
                }
				close(fd);
				fd = open("/tmp/icidoc", O_RDONLY);
				node->fd_in = fd;
            }
		ft_redirect(node, data);
	}
	if (g_sig_handle == SIGINT)
		data->last_error = 130;
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler);
}