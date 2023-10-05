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

t_token *next_pipe(t_token *token)
{
    while(token && token->type != PIPE && token->next)
        token = token->next;
    if (token->type == PIPE)
        return(token);
    else
        return (NULL);
}

t_token *last_cmd(t_token *token)
{
    while (token->next)
        token = token->next;
    while(token->type_2 != COMMAND && token->previous)
        token = token->previous;
    return (token);
}

t_token *previous_cmd(t_token *token)
{
    while(token->previous && token->type_2 != COMMAND)
        token = token->previous;
    return(token);
}

t_node *first_node(t_node *node)
{
    while (node && node->up)
        node = node->up;
    return(node);
}

void print_branch(t_node *node)
{
    t_node *tmp_node;

    tmp_node = node;
 
    if (node->left)
    {
        node = node->left;
        print_node(node);
    }
    print_node(tmp_node);
    /*while (node->left)
    {
        node = node->left;
        print_node(node);
    }   
    while(node && node->up)
        node = node->up;
    print_node(node);

    if (node->right)
    {
        node = node->right;
        print_tree(node);
    }*/
}

void print_tree(t_node *node)
{
    while(node && node->right)
    {
        print_branch(node);
        node = node->right;
    }
    if (node)
        print_branch(node);
}

t_node *init_tree(t_token *token)
{
    t_node *node;
    t_node *temp_node;

    if (token && next_pipe(token) && token->next)
    {
        node = make_pip(next_pipe(token));
        node->up = NULL;
        token = (next_pipe(token))->next;
    }
    while (token && next_pipe(token) && token->next)
    {
        node->right = make_pip(next_pipe(token));
        temp_node = node;
        node = node->right;
        node->up = temp_node;
        token = (next_pipe(token))->next;
    }
    node->right = make_cmd(last_cmd(token));
    temp_node = node;
    node = node->right;
    node->up = temp_node;
    return(first_node(node));
}

