/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:15:16 by rshay             #+#    #+#             */
/*   Updated: 2023/09/26 15:03:47 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    prompt(char **envp)
{
    char    *commande;
    //t_token *token;
    while (1)
    {
        commande = readline("$");
        if (!ft_strncmp(commande, "exit", 4))
        {
            free(commande);
            break;
        }

    //token = lexer(commande, envp);
    //print_token(token);

        process(commande, envp);

        add_history(commande);
        free(commande);
    }
}