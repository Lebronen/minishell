/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:04 by rshay             #+#    #+#             */
/*   Updated: 2023/09/26 15:40:36 by rshay            ###   ########.fr       */
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

void    env(char **envp)
{
    int i;
    if (!envp)
        ft_printf("env error\n");
    i = 0;
    while (envp[i])
    {
        ft_printf("%s\n", envp[i]);
        i++;
    }
}

void    echo(char *str, int option, int fd)
{
    ft_putstr_fd(str, fd);
    if (!option)
        ft_putchar_fd('\n', fd);
}