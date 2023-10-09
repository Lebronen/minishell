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
    printf("node type : %d\n", node->type);
    while(node->str_options[i])
    {
        printf("options :%s\n", node->str_options[i]);
        i++;
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
    return (str);
}

t_node *make_cmd(t_token *token, t_node *up)
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
    node->str_options = malloc((i+1) * sizeof(char*));
    if (!node->str_options)
        return (NULL);
    node->type = CMD;
    node->str_options = cmd_str(tmp_token, node->str_options);
    node->left = NULL;
    node->right = NULL;
    node->up = up;
    return (node);
}

t_node  *nodizer(t_token *token)
{
    while(token)
    {
        t_node  *node;

        if (token->type_2 == COMMAND)
        {
            node = make_cmd(token, NULL);
            print_node(node);
        }
        else
            node = NULL;
        /*if (token->type_2 == REDIR)
            make_rdr(token);
        if(token->type == PIPE)
            make_pip(token);*/
        token = token->next;
    }
    return (NULL);
}