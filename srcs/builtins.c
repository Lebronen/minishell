/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:04 by rshay             #+#    #+#             */
/*   Updated: 2023/11/02 15:03:34 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd(char *path)
{
    struct stat    buf;
    mode_t          mode;
    
    stat(path, &buf);
    mode = buf.st_mode;
    if (chdir(path) < 0)
    {
        if (access(path, F_OK))
            ft_printf("No such file or directory\n");
        else if (!S_ISDIR(mode))
            ft_printf("cd: not a directory: %s\n", path);
        else if (!(mode & S_IXUSR))
            ft_printf("cd: permission denied: %s\n", path);
    }
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
    if (write(fd, str, ft_strlen(str)) == -1)
        ft_printf("write error\n");
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
    while (current)
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

void    unset(char *commande, t_list *envp)
{
    t_list  *current;
    t_list  *next;
    
    current = envp;
    while (current && current ->next)
    {
        if (!ft_strncmp(current->next->content, commande, ft_strlen(commande)))
        {
            next = current->next->next;
            ft_lstdelone(current->next, &del);
            current->next = next;
        }
        current = current->next;
    }
}
