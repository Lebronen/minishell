/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:06:05 by rshay             #+#    #+#             */
/*   Updated: 2023/11/02 16:15:09 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int     is_builtin(char **commande, t_list *envp)
{
    
    if (!ft_strncmp(commande[0], "cd", 2))
    {
        cd(commande[1]);
        return (1);
    }
    else if (!ft_strncmp(commande[0], "pwd", 3))
    {
        pwd();
        return (1);
    }
    else if (!ft_strncmp(commande[0], "env", 3))
    {
        env(envp);
        return (1);
    }
    else if (!ft_strncmp(commande[0], "echo", 4))
    {
        if (!ft_strncmp(commande[1], "-n", 2))
        {
            if (commande[2])
                echo(commande[2], 1, 1);
        }
        else
            echo(commande[1], 0, 1);
        return (1);
    }
    else if (!ft_strncmp(commande[0], "export", 6))
    {
        export(commande[1], envp);   
        return (1);
    }
    else if (!ft_strncmp(commande[0], "unset", 5))
    {
        unset(commande[1], envp);   
        return (1);
    }
    return (0);
}

