/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:15:16 by rshay             #+#    #+#             */
/*   Updated: 2023/10/28 16:16:35 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    prompt(t_list *envp)
{
    char    *commande;
    t_token *token;
    t_node *node;
    
    node = NULL;
    while (1)
    {
        commande = readline("$");
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

        commande = env_value_checker(commande, envp);
        token = lexer(commande, envp);
        node = nodizer(token, envp);
        print_node(node);

        //process(node, envp);
        add_history(commande);

        free(commande);
        free_lexer(token);
        free_nodes(node);
    }
}