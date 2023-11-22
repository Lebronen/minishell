/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:33:18 by lebronen          #+#    #+#             */
/*   Updated: 2023/11/22 17:45:46 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void wait_for_childrens(int nb)
{
    int i;

    i = 0;
    while (i <= nb)
    {
        wait(NULL);
        i++;
    }
}

void    free_pipes(int **fd, int nb)
{
    int i;

    i = 0;
    while (i < nb)
    {
        free(fd[i]);
        i++;
    }
    free(fd);
}

void    close_pipes(int **fd, int nb)
{
    int i;

    i = 0;
    while (i < nb)
    {
        close(fd[i][0]);
        close(fd[i][1]);
        i++;
    }
}