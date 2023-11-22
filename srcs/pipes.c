/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:46:18 by lebronen          #+#    #+#             */
/*   Updated: 2023/11/22 18:35:54 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    child_process(t_node *tmp, int *fd1, int *fd2, int i)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        error();
    if (pid == 0)
    {
        if (i == 0 )
        {
            if (tmp->fd_in != STDIN_FILENO)
                dup2(tmp->fd_in, STDIN_FILENO);
        }
        else 
            dup2(fd2[0], STDIN_FILENO);
        dup2(fd1[1], STDOUT_FILENO);
        close(fd1[0]);
        close(fd1[1]);
        if (i)
        {    
            close(fd2[0]);
            close(fd2[1]);
        }
        execute(tmp->str_options, tmp->data);
    }
}

void    parent_process(t_node *tmp, int *fd1, int *fd2, int i)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        error();
    if (pid == 0)
    {
        if (tmp->fd_out != STDOUT_FILENO)
            dup2(tmp->fd_out, STDOUT_FILENO);
        dup2(fd1[0], STDIN_FILENO);
        close(fd1[0]);
        close(fd1[1]);
        if (i > 1)
        {    
            close(fd2[0]);
            close(fd2[1]);
        }
        execute(tmp->str_options, tmp->data);
    }
}

int	    nb_pipes(t_node *node)
{
	t_node  *current;
    int     i;

    current = node;
    i = 0;
    while (current->next)
    {
        i++;
        current = current->next;
    }
    return (i);
}

void    ft_pipe(t_node *node)
{
   
    int     tube1[2];
    int     tube2[2]; 
    t_node  *tmp;
    int     i;
    int     nb;
    
   tmp = node;
   nb = nb_pipes(node);
   i = 0;
   while (i < nb)
   {
        if (i % 2 == 0)
        {
            pipe(tube1);
            child_process(tmp, tube1, tube2, i);
        }
        else
        {
            pipe(tube2);
            child_process(tmp, tube2, tube1, i);
        }
        i++;
        tmp = tmp->next;
    }
    if (i % 2)
        parent_process(tmp, tube1, tube2, i);
    else
        parent_process(tmp, tube2, tube1, i);
    close(tube1[0]);
    close(tube1[1]);
    if (nb > 1)
    {
        close(tube2[0]);
        close(tube2[1]);
    }
   wait_for_childrens(nb);
}