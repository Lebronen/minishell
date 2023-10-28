/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:10:40 by rshay             #+#    #+#             */
/*   Updated: 2023/10/28 16:56:18 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int nb_str(char *s, char c)
{
    int i;

    i = 0;
    while (*s++)
    {
        if (c == *s)
            i++;
    }
    return (i);
}

void	child_process(char **commande, t_list *envp, int *fd)
{
	int		filein;

	filein = open("/dev/stdin", O_RDONLY, 0644);
	if (filein == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	execute(commande, envp);
}

void	parent_process(char **commande, t_list *envp, int *fd)
{
	int		fileout;

	fileout = open("/dev/stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(commande, envp);
}

void    ft_pipe(t_node *node, t_list *envp)
{
    int     fd[2];
    pid_t   pid;
    t_node  *current;

    current = node;
    while (current)
    {
        fd[0] = current->fd_in;
       if (pipe(fd) == -1)
               error();
            pid = fork();
            if (pid == -1)
                error();
            if (pid == 0)
                child_process(current->str_options, envp, fd);
        current = current->next;
    }
            pid = fork();
            if (pid == -1)
                error();
            if (pid == 0)
                parent_process(current->str_options, envp, fd);
            current = node;
            while (current)
            {
                wait(NULL);
            }
}
/*
void    ft_redirect_out(char *commande, t_list *envp)
{
    char    **list_command;
    pid_t   pid;
    int     fileout;
    int     status;

    list_command = ft_split(commande, '>');
    pid = fork();
    if (pid == -1)
        error();
    if (pid == 0)
    {
        fileout = open(list_command[1] + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fileout, STDOUT_FILENO);
        execute(list_command[0], envp);
        close(fileout);
        dup2(STDOUT_FILENO, STDOUT_FILENO);
    }
    else
        waitpid(pid, &status, 0);
    
}
*/
/*
void    ft_redirect_in(char *commande, t_list *envp)
{
    char    **list_command;
    pid_t   pid;
    int     filein;
    int     status;

    list_command = ft_split(commande, '<');
    pid = fork();
    if (pid == -1)
        error();
    if (pid == 0)
    {
        filein = open(list_command[1] + 1, O_RDWR , S_IRUSR | S_IWUSR | O_CREAT, 0644);
        if (filein < 0)
            ft_printf("file not found\n");
        if (dup2(filein, STDIN_FILENO) < 0)
            ft_printf("dup2 error\n");
        close(filein);
        execute(list_command[0], envp);
    }
    else
        waitpid(pid, &status, 0);
}

void    ft_double(char *commande, t_list *envp)
{
    char    **list_command;
    pid_t   pid;
    int     fileout;
    int     status;

    list_command = ft_split(commande, '>');
    pid = fork();
    if (pid == -1)
        error();
    if (pid == 0)
    {
        fileout = open(list_command[1] + 1, O_CREAT | O_RDWR | O_APPEND,  S_IRUSR | S_IWUSR );
        dup2(fileout, STDOUT_FILENO);
        execute(list_command[0], envp);
        close(fileout);
        dup2(STDOUT_FILENO, STDOUT_FILENO);
    }
    else
        waitpid(pid, &status, 0);
}
*/