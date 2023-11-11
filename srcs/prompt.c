/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:15:16 by rshay             #+#    #+#             */
/*   Updated: 2023/11/03 15:47:02 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_heredoc(t_node *node)
{
    while(node)
    {
        if (node->fd_in == -2 && node->heredoc == NULL)
            return (0);
        node = node->next;
    }
    return (1);    
}

void    prompt(t_data *data)
{
    char    *commande;
    t_token *token;
    t_node *node;


    node = NULL;
    

    while (1)
    {
        commande = readline("$");
        if(!commande)
        {
            ft_putstr_fd("exit\n", 1);
            break;
        }
        while (error_cmd(commande))
        {
            free(commande);
            commande = readline("$");
        }
        if (!ft_strncmp(commande, "exit", 4))
        {
            free(commande);
            break;
        }
        commande = env_value_checker(commande, data->envp);
        token = lexer(commande, data->envp);
        node = nodizer(token, data);

        if(check_heredoc(node))
        {
            print_node(node);
            process(node, data->envp);
            add_history(commande);
        }
        else
            printf("probleme heredoc\n");
        free(commande);
        free_lexer(token);
        free_nodes(node);
    }
    rl_clear_history();
}