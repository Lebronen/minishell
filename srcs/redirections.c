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

void    manage_heredoc(t_node *node, t_token *token)
{
    int i;
    t_token *tmp_token;

    i = 0;
    tmp_token = token;
    if (node->fd_in != -2)
    {
        node->heredoc = NULL;
        return ;
    }
    while (token && token->type != PIPE)
    {
        if (token->type_2 == ENDOF)
            i++;
        token = token->next;
    }
    node->heredoc = malloc(sizeof(char *) * (i + 1));
    if (!node->heredoc)
        return ;
    i = 0;
    while (tmp_token)
    {
        if (tmp_token->type_2 == ENDOF)
        {
            node->heredoc[i] = ft_strdup(tmp_token->next->str);
            i++;
        }
        tmp_token = tmp_token->next;
    }
    node->heredoc[i] = NULL;
}

int init_in(t_token *token)
{
    int fd;

    fd = -1;

    while(token && token->type != PIPE)
    {
        if (token->type_2 == IN)
        {
            if (fd != -1 && fd != -2)
                close(fd);
            fd = open(token->next->str, O_RDONLY);
            if (fd == -1)
                return (-1);
        }
        else if (token->type_2 == ENDOF)
        {
            if (fd != -1 && fd != -2)
                close(fd);
            return (-2);
        }
        token = token->next;
    }
    return (fd);
}



//un heredoc et ou un entree !!??
//si heredoc, pas de < analyse



//si heredoc -> pas de fd mais char * (EOF)
//si pas de heredocs (pas de char * (free si on en avait deja eu un ))