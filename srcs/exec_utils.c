/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:10:40 by rshay             #+#    #+#             */
/*   Updated: 2023/11/03 17:38:08 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int nb_str(char *s, char c)
{
    int i;

    i = 0;
    while (*s++)
    {
        if (c == *s)
            i++;
    }
    return (i);
}

void	child_process(char **commande, t_list *envp, int *fd)
{
	int		filein;

	filein = open("/dev/stdin", O_RDONLY, 0644);
	if (filein == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(commande, envp);
}

void	parent_process(char **commande, t_list *envp, int *fd)
{
	int		fileout;

	fileout = open("/dev/stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(commande, envp);
}

void    ft_pipe(t_node *node, t_list *envp)
{
    int     fd[2];
    pid_t   pid;
    t_node  *current;

    current = node;
    while (current)
    {
        fd[0] = current->fd_in;
       if (pipe(fd) == -1)
               error();
            pid = fork();
            if (pid == -1)
                error();
            if (pid == 0)
                child_process(current->str_options, envp, fd);
        current = current->next;
    }
            pid = fork();
            if (pid == -1)
                error();
            if (pid == 0)
                parent_process(current->str_options, envp, fd);
            current = node;
            while (current)
            {
                wait(NULL);
            }
}

void    ft_redirect(t_node *node, t_list *envp)
{
    pid_t   pid;
    int     status;
    int     fd;
    int     i;

    pid = fork();
    if (pid == -1)
        error();
    if (pid == 0)
    {
        if (node->fd_out != STDOUT_FILENO)
        {    
            dup2(node->fd_out, STDOUT_FILENO);
            close(node->fd_out);
        }
        if (node->fd_in != STDIN_FILENO)
        {
            fd = node->fd_in;
            if (node->fd_in == -2)
            {
                i= 0;
                fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
                if (fd == -1)
                    error();
                while (node->heredoc[i])
                {
                    ft_putstr_fd(node->heredoc[i], fd);
                    i++;
                }
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        execute(node->str_options, envp);
        dup2(STDOUT_FILENO, STDOUT_FILENO);
    }
    else
        waitpid(pid, &status, 0);
    
}