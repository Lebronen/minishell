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

void    print_node(t_node *node)
{
    int i;

    i = 0;

    while (node)
    {
        i = 0;
        if(node->str_options != NULL)
        {
            printf("CMD:\n");
            while(node->str_options && node->str_options[i])
            {
                printf("%s\n", node->str_options[i]);
                i++;
            }
        }
        if(node->heredoc != NULL)
        {
            printf("heredoc:\n");
            while(node->heredoc && node->heredoc[i])
            {
                printf("%s\n", node->heredoc[i]);
                i++;
            }
        }
        printf("fd_in -> %d\n", node->fd_in);
        printf("fd_out -> %d\n", node->fd_out);
        node = node->next;
    }
}


char **cmd_str(t_token *token, char **str)
{
    int i;

    i = 1;
    str[0] = ft_strdup(token->str);
    token = token->next;
    while (token && (token->type_2 == OPTION || token->type_2 == ARG))
    {
        str[i] = ft_strdup(token->str);
        token = token->next;
        i++;
    }
   str[i] = NULL;
    if (str)
        return (str);
    return (NULL);
}

t_node *make_cmd(t_token *token)
{
    t_node *node;
    t_token *tmp_token;
    int i;

    i = 0;
    tmp_token = token;
    node = malloc(sizeof(t_node));
    if(!node)
        return (NULL);
    while(token->next && (token->next->type_2 == OPTION || token->next->type_2 == ARG))
    {
        i++;
        token = token->next;
    }
    node->str_options = malloc((i + 2) * sizeof(char *));
    if (!node->str_options)
        return (NULL);
    node->str_options = cmd_str(tmp_token, node->str_options);
    node->next = NULL;
    return (node);
}

t_node  *nodizer_unit(t_token *token)
{
    t_token *tmp_token;
    t_node  *node;

    tmp_token = token;
    node = NULL;
    while(token && token->type != PIPE)
    {
        if (token->type_2 == COMMAND)
            node = make_cmd(token);
        token = token->next;
    }
    if (!node)
    {
        node = malloc(sizeof(t_node));
        if(!node)
            return (NULL);
        node->str_options = NULL;
        node->next = NULL;
    }
    node->fd_in = init_in(tmp_token);
    node->fd_out = init_out(tmp_token);
    manage_heredoc(node, tmp_token);
    return (node);
}

t_token *next_unit(t_token *token)
{
    while(token && token->type != PIPE)
        token = token->next;
    if (token && token->type == PIPE)
        return (token->next);
    else
        return (NULL);
}

t_node  *nodizer(t_token *token)
{
    t_token *tmp_token;
    t_node *node;
    t_node *tmp_node;
    t_node *prev;

    tmp_token = token;
    prev = NULL;
    while (token)
    {
        node = nodizer_unit(token);
        node->prev = prev;
        prev = node;
        token = next_unit(token);
    }
    while(node->prev)
    {
        tmp_node = node;
        node = node->prev;
        node->next = tmp_node;
    }
    return (node);
}

void    free_nodes(t_node *node)
{
    int i;
    t_node *temp_node;

    while(node)
    {
        i = 0;
        if (node->str_options)
        {
            while(node->str_options[i])
            {
                free(node->str_options[i]);
                i++;
            }
            free(node->str_options);
        }
        i = 0;
        if (node->heredoc)
        {
            while(node->heredoc[i])
            {
                free(node->heredoc[i]);
                i++;
            }
            free(node->heredoc);
        }
        temp_node = node->next;
        if (node)
            free(node);
        node = temp_node;
    }
}

