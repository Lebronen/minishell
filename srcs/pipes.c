/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:46:18 by lebronen          #+#    #+#             */
/*   Updated: 2023/11/29 12:38:32 by lebronen         ###   ########.fr       */
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
        if (tmp->fd_in != STDIN_FILENO)
            ft_redirect_in(tmp, tmp->data);
        else
        {
            if (i) 
                dup2(fd2[0], STDIN_FILENO);
        }
        if (tmp->fd_out != STDOUT_FILENO)
            ft_redirect_out(tmp);
        else
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

int    parent_process(t_node *tmp, int *fd1, int *fd2, int nb)
{
    pid_t   pid;
    int     in;
    int     out;

    if (is_builtin(tmp->str_options) && !is_only_builtin(tmp->str_options))
    {
        in = dup(STDIN_FILENO);
        out = dup(STDOUT_FILENO);
        ft_redirect_in(tmp, tmp->data);
        ft_redirect_out(tmp);
        is_builtin_exec(tmp->str_options, tmp->data);
        dup2(in, STDIN_FILENO);
        close(in);
        dup2(out, STDOUT_FILENO);
        close(out);
        return (1);
    }
    pid = fork();
    if (pid == 0)
    {
        if (tmp->fd_in != STDIN_FILENO)
            ft_redirect_in(tmp, tmp->data);
        else
        {
            if (nb)
            {
                dup2(fd1[0], STDIN_FILENO);
                close(fd1[0]);
                close(fd1[1]);
                if (nb > 1)
                {    
                    close(fd2[0]);
                    close(fd2[1]);
                }
            }
        }
        ft_redirect_out(tmp);
        exec_cmd(tmp, tmp->data, nb);
    }
    return (0);
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

void    ft_last_cmd(t_node *node, int *fd1, int *fd2, int nb)
{
    if (nb % 2)
            nb -= parent_process(node, fd1, fd2, nb);
    else
            nb -= parent_process(node, fd2, fd1, nb);
    if (nb)
    {
        close(fd1[0]);
        close(fd1[1]);
        if (nb > 1)
        {
            close(fd2[0]);
            close(fd2[1]);
        }
        
    }
   wait_for_childrens(nb);
}

void    ft_pipe(t_node *node, int *fd1, int *fd2, int nb)
{
    int     i;
    t_node  *tmp;

    i = 0;
    tmp = node;
    while (i < nb)
    {
        if (is_only_builtin(tmp->str_options))
        {
            if (!i)
                fd2[0] = STDIN_FILENO;
        }
        else
        {
            write(2, "pipe process\n", 14);
            if (i % 2 == 0)
            {
                pipe(fd1);
                child_process(tmp, fd1, fd2, i);
            }
            else
            {
                pipe(fd2);
                child_process(tmp, fd2, fd1, i);
            }
            i++;
        }
        tmp = tmp->next;
    }
    ft_last_cmd(node, fd1, fd2, nb);
}