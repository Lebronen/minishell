/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:10:40 by rshay             #+#    #+#             */
/*   Updated: 2023/11/08 11:54:20 by lebronen         ###   ########.fr       */
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

void	child_process(t_node *node, t_list *envp, int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	dup2(node->fd_in, STDIN_FILENO);
	close(fd[0]);
	execute(node->str_options, envp);
}

void	parent_process(t_node *node, t_list *envp, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(node->fd_out, STDOUT_FILENO);
	close(fd[1]);
	execute(node->str_options, envp);
}

void	pipe_process(t_node *node, t_list *envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(node->str_options, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
        wait(NULL);
	}
}

/*
void    ft_pipe(t_node *node, t_list *envp)
{
    t_node  *current;
    pid_t   pid;
    
    current = node;
    dup2(current->fd_in, STDIN_FILENO);
    while (current->next)
    {
        pipe_process(current, envp);    
        current = current->next;
    }
            pid = fork();
            if (pid == -1)
                error();
            if (pid == 0)
                parent_process(current->str_options, envp, node->fd_in);
            current = node;
            while (current)
            {
                wait(NULL);
            }
}
*/

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
        if (is_builtin(node->str_options, envp))
            exit(0) ;
        execute(node->str_options, envp);
        dup2(STDOUT_FILENO, STDOUT_FILENO);
    }
    else
        waitpid(pid, &status, 0);
    
}