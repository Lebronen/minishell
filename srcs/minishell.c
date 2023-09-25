/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:30:45 by rshay             #+#    #+#             */
/*   Updated: 2023/09/21 16:36:04 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    char	**env;

    env = init_env(envp);
    
    if (argc == 1)
    {
        prompt(env);
    }
    else
    {
        ft_putstr_fd("Erreur : lancez uniquement l'executable sans argument", 2);
    }
}
