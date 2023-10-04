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

void print_node(t_node *node)
{
    int i;

    i = 0;
    printf("node type : %d\n", node->type);
    printf ("node content :\n");
    while(node->str_options[i])
    {
        printf("%s\n", node->str_options[i]);
        i++;
    }
}

// jenvoie un token cmd pour creer un node cmd
t_node  *make_cmd(t_token *token)
{
    t_node  *cmd_node;
    int     i;


    t_token *tmp_token;
    i = 0;
    tmp_token = token;
    token = token->next;
    while (token && (token->type_2 == OPTION || token->type_2 == ARG))
    {
        i++;
        token = token->next;
    }
    cmd_node = malloc(sizeof(t_node *));
    if (!cmd_node)
        return (NULL);
    cmd_node->str_options = malloc(sizeof(char *) * (i + 1));
    if(!cmd_node->str_options)
        return(NULL);
    i = 1;
    token = tmp_token;
    cmd_node->str_options[0] = ft_strdup(token->str);
    token = token->next;
    while(token && (token->type_2 == OPTION || token->type_2 == ARG))
    {
        cmd_node->str_options[i] = ft_strdup(token->str);
        token = token->next;
        i++;
    }
    cmd_node->str_options[i] = NULL;
    cmd_node->type = CMD;
    print_node(cmd_node);
    return (cmd_node);
}

t_node  *make_rdr(t_token *token)
{

}

t_node  *nodizer(t_token *token)
{
    while(token)
    {
        if (token->type_2 == COMMAND)
            make_cmd(token);
        token = token->next;
    }
    return (NULL);
}