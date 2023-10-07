/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:23:28 by rshay             #+#    #+#             */
/*   Updated: 2023/10/03 15:24:20 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char    **add_env(char *ligne, t_list envp)
{
    char    **new;
    int     i;

    i = 0;
    while (envp[i])
        i++;
    new = malloc ((i + 1) * sizeof(char *));
    i = 0;
    while (envp[i])
    {
        new[i] = ft_strdup(envp[i]);
        i++;
    }
    new[i] = ft_strdup(ligne);
    return (new);
}

char    **supp_env(char *ligne, t_list envp)
{
    char    **new;
    int     i;
    int     here;

    i = 0;
    here = 0;
    while (envp[i])
    {
        if (!strncmp(envp[i], ligne, ft_strlen(ligne)))
            here = 1;
        i++;
    }
    new = malloc((i - here) * sizeof(char *));
    i = 0;
    while (envp[i])
    {
        if (strncmp(ligne, envp[i], ft_strlen(ligne)))
        {
            new[i] = ft_strdup(envp[i]);
            i++;
        }
    }
    return (new);
}

char    **tabcpy(char **tab)
{
    char    **dst;
    int     i;

    i = 0;
    while (tab[i])
        i++;
    dst = malloc(i * sizeof(char *));
    i = 0;
    while (tab[i])
    {
        dst[i] = ft_strdup(tab[i]);
        i++;
    }
    return (dst);
}
*/