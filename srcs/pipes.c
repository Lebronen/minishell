/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:46:18 by lebronen          #+#    #+#             */
/*   Updated: 2023/11/16 22:03:47 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_node *node, t_list *envp, int *fd)
{
	pid_t	pid;
    
	pid = fork();
	if (pid == -1)
		error();
	else if (pid == 0)
	{
        close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(node->str_options, envp);
	}
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        waitpid(pid, NULL, 0);
    }
        
}

void    create_pipe(int **fd, int nb)
{
    int i;

    i = 0;
    while (i < nb)
    {
        if (pipe(fd[i]) == -1)
        {
            perror("pipe error\n");
            exit(0);
        }
        i++;
    }
    
}

int	    nb_pipes(t_node *node)
{
	t_node  *current;
    int     i;

    current = node;
    i = 0;
    while (current->next)
    {
        i++;
        current = current->next;
    }
    return (i);
}

void    ft_pipe(t_node *node, t_list *envp)
{
    int     **fd;
    int     nb;
    int     i;
    t_node  *tmp;
    
    nb = nb_pipes(node);
    i = 0;
    tmp = node;
    fd = malloc(nb * sizeof(int *));
    while (i < nb)
    {
        fd[i] = malloc(2 * sizeof(int));
        i++;
    }
    create_pipe(fd, nb);
    i = 0;
    while (i < nb)
    {
        child_process(tmp, envp, fd[i]);
        i++;
        tmp = tmp->next;
    }
    free_pipes(fd, nb);
    dup2(STDIN_FILENO, STDIN_FILENO);
    dup2(STDOUT_FILENO, STDOUT_FILENO);
    execute(tmp->str_options, envp);
    
}