/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:15:16 by rshay             #+#    #+#             */
/*   Updated: 2023/10/03 15:41:33 by rshay            ###   ########.fr       */
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
            if(commande)
                free(commande);
            break;
        }

        token = lexer(commande, envp);
        node = nodizer(token);

        process(commande, envp);
        add_history(commande);

        free(commande);
        free_lexer(token);
        free_nodes(node);
        //free_list(envp); A AJOUTER
    }
}