/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:05:27 by lebronen          #+#    #+#             */
/*   Updated: 2023/11/29 11:16:17 by lebronen         ###   ########.fr       */
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

int  ft_heredoc(t_node *node, t_data *data)
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

void    ft_redirect_in(t_node *node, t_data *data)
{
    int fd;

    if (node->fd_in != STDIN_FILENO)
    {
        fd = node->fd_in;
        if (fd == -2)
            fd = ft_heredoc(node, data);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

}

void    ft_redirect_out(t_node *node)
{
     if (node->fd_out != STDOUT_FILENO)
    {   
        dup2(node->fd_out, STDOUT_FILENO);
        close(node->fd_out);
    }
}

void    exec_cmd(t_node *node, t_data *data, int nb)
{
    
    if (nb && is_only_builtin(node->str_options))
        return ;
    execute(node->str_options, data);
}

void    execloop(t_node *node)
{
    int  tube1[2];
    int  tube2[2]; 
    int  nb;
        
   nb = nb_pipes(node);
   ft_pipe(node, tube1, tube2, nb);
   
}