/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:30:45 by rshay             #+#    #+#             */
/*   Updated: 2023/10/03 15:11:36 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main(int argc, char **argv, char **envp)
{
    (void)argv;
    t_data *data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    data->last_error = 0;
    data->envp = tab_to_list(envp);
    signal_loop(data);
    
    if (argc == 1)
    {
        prompt(data);
    }
    else
    {
        ft_putstr_fd("Erreur : lancez uniquement l'executable sans argument", 2);
    }
    free_data(data);
}
