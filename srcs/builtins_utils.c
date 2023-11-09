/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:06:05 by rshay             #+#    #+#             */
/*   Updated: 2023/10/28 17:23:00 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (1);
    }
    if (*s1 != *s2)
    {
        if (*s1 != '\n' || *s2 == '\n')
            return (0);
            
        return (1);
    }
    return (0);
}

int     is_builtin(char **commande)
{
    
    if (!ft_strcmp(commande[0], "cd"))
    {
        cd(commande[1]);
        return (1);
    }
    else if (!ft_strcmp(commande[0], "pwd"))
    {
        pwd();
        return (1);
    }
    else if (!ft_strcmp(commande[0], "env"))
        return (1);
    else if (!ft_strcmp(commande[0], "echo"))
        return (1);
    else if (!ft_strcmp(commande[0], "export"))
        return (1);
    else if (!ft_strcmp(commande[0], "unset"))
        return (1);
    return (0);
}

