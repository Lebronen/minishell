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
    

    if (node->type == RDR)
        printf("redirection type %d\nchemin : %s\n", node->rdr_type, node->path);
    if (node->type == PIP)
        printf("PIIIIIIPE\n");
    if(node->type == CMD)
    {
        printf ("node CMD->");
        while(node->str_options[i])
       {
            printf("%s\n", node->str_options[i]);
           i++;
        }
    }
}

t_node  *make_rdr(t_token *token)
{
    t_node *rdr_node;

    rdr_node = malloc(sizeof(t_node));
    if (!rdr_node)
        return (NULL);
    rdr_node->type = RDR;
    rdr_node->rdr_type = token->type_2;
    rdr_node->path = token->next->str;
    rdr_node->right = NULL;
    rdr_node->left = NULL;
    rdr_node->up = NULL;
   // print_node(rdr_node);
    return (rdr_node);
}

void init_rdr_nodes(t_token *token, t_node *node)
{
    t_node *temp_node;
    t_node *cmd_node;


    cmd_node = node;
    while(token && token->previous && token->previous->type != PIPE)
        token = token->previous;
    while(token && token->next && token->next->type != PIPE)
    {
        if (token->type == REDIR)
        {
            node->left = make_rdr(token);
            temp_node = node;
            node = node->left;
            node->up = temp_node;
        }
        token = token->next;
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
   
   
    //print_node(cmd_node);
    init_rdr_nodes(tmp_token, cmd_node);
    return (cmd_node);
}

t_node *make_pip(t_token *token)
{
    t_node  *pip_node;
    t_node  *temp_node;

    pip_node = malloc(sizeof(t_node));
    if(!pip_node)
        return(NULL);
    pip_node->type = PIP;
    pip_node->left = make_cmd(previous_cmd(token));
    temp_node = pip_node->left;
    temp_node->up = pip_node;
   // print_node(pip_node);
    return(pip_node);
}


/*t_node  *nodizer(t_token *token)
{
    while(token)
    {
        if (token->type == REDIR)
            make_rdr(token);
        if (token->type_2 == COMMAND)
            make_cmd(token);
        if(token->type == PIPE)
            make_pip(token);
        token = token->next;
    }

    return (NULL);
}*/