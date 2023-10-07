/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:04 by rshay             #+#    #+#             */
/*   Updated: 2023/10/07 17:49:52 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd(char *path)
{
    if (chdir(path) < 0)
        ft_printf("No such file or directory\n");
}

void    pwd()
{
    char    cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        ft_printf("getcwd error\n");
    else
        ft_printf("%s\n", cwd);
}

void    env(t_list *envp)
{
    t_list  *current;
    if (!envp)
        ft_printf("env error\n");
    current = envp;
    while (current)
    {
        ft_printf("%s\n", current->content);
        current = current->next;
    }
}

void    echo(char *str, int option, int fd)
{
    ft_putstr_fd(str, fd);
    if (!option)
        ft_putchar_fd('\n', fd);
}

void    export(char *commande, t_list *envp)
{
    t_list  *current;
    t_list  *new;
    int     here;
    
    here = 0;
    current = envp;
    while (current->next)
    {
        if (!ft_strncmp(current->content, commande, ft_index(commande, '=')))
        {
            current->content = ft_strdup(commande);
            here = 1;
        }
        current = current->next;
    }
    if (!here)
    {
        new = ft_lstdupnew(commande);
        ft_lstadd_back(&envp, new);
    }
}
