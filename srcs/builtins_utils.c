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

