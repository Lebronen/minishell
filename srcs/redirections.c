/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:31:31 by cgermain          #+#    #+#             */
/*   Updated: 2023/09/25 11:13:36 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     init_out(t_token *token)
{
    int fd;

    fd = -1;
    while(token && token->type != PIPE)
    {
        if (token->type_2 == OUT)
        {
            if (fd != -1)
                close(fd);
            fd = open(token->next->str, O_TRUNC | O_CREAT, 0644);
            if (fd == -1)
                return (-1);
        }
        if (token->type_2 == APPEND)
        {
            if (fd != -1)
                close(fd);
            fd = open(token->next->str, O_APPEND | O_CREAT, 0644);
            if (fd == -1)
                return (-1);
        }
        token = token->next;
    }
    return (fd);
}

int has_heredoc(t_token *token)
{
    while(token && token->type != PIPE)
    {
        if (token->type_2 == EOF)
            return (1);
        token = token->next;
    }
    return (0);
}

int init_in(t_token *token)
{
    int fd;

    fd = -1;
    while(token && token->type != PIPE)
    {
        if (token->type_2 == IN)
        {
            if (fd != -1)
                close(fd);
            fd = open(token->next->str, O_RDONLY);
            if (fd == -1)
                return (-1);
        }
        token = token->next;
    }
    return (fd);
}



//un heredoc et ou un entree !!??
//si heredoc, pas de < analyse



//si heredoc -> pas de fd mais char * (EOF)
//si pas de heredocs (pas de char * (free si on en avait deja eu un ))