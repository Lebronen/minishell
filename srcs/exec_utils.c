/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:10:40 by rshay             #+#    #+#             */
/*   Updated: 2023/11/27 14:10:01 by lebronen         ###   ########.fr       */
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

int     ft_heredoc(t_node *node, t_data *data)
{
    int fd;
    int i;

    i = 0;
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
    return (fd);
}

void    ft_redirect(t_node *node, t_data *data)
{
    pid_t   pid;
    int     status;
    int     fd;

    
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
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        execute(node->str_options, data);
    }
    else
        waitpid(pid, &status, 0);
    
}