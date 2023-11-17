/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:06:05 by rshay             #+#    #+#             */
/*   Updated: 2023/11/17 16:42:38 by lebronen         ###   ########.fr       */
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

int     is_builtin(char **commande, t_data *data)
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
        env(data->envp);
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
        export(commande[1], data->envp);   
        return (1);
    }
    else if (!ft_strncmp(commande[0], "unset", 5))
    {
        unset(commande[1], data->envp);   
        return (1);
    }
    return (0);
}
/*
int is_builtin(char *str)
{
    if (!ft_strncmp(str, "cd", 2))
        return (1);
    else if (!ft_strncmp(str, "pwd", 3))
        return (1);
    else if (!ft_strncmp(str, "env", 3))
        return (1);
    else if (!ft_strncmp(str, "echo", 4))
        return (1);
    else if (!ft_strncmp(str, "export", 6))
        return (1);
    else if (!ft_strncmp(str, "unset", 5))
        return (1);
    return (0);
}
*/