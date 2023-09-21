/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:15:16 by rshay             #+#    #+#             */
/*   Updated: 2023/06/19 16:50:29 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    prompt(char **envp)
{
    char    *commande;

    while (1)
    {
        commande = readline("$");
        if (!ft_strncmp(commande, "exit", 4))
        {
            free(commande);
            break;
        }

        process(commande, envp);

        add_history(commande);
        free(commande);
    }
}