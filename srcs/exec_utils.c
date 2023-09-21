/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:10:40 by rshay             #+#    #+#             */
/*   Updated: 2023/09/21 16:30:36 by rshay            ###   ########.fr       */
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

void	child_process(char *commande, char **envp, int *fd)
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

void	parent_process(char *commande, char **envp, int *fd)
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

void    ft_pipe(char *commande, char **envp)
{
    char **list_commandes;
    int     fd[2];
    pid_t   pid;
    int     i;

    list_commandes = ft_split(commande, '|');
    i = 0;
    while (i < nb_str(commande, '|'))
    {
        
        if (pipe(fd) == -1)
                error();
            pid = fork();
            if (pid == -1)
                error();
            if (pid == 0)
                child_process(list_commandes[i], envp, fd);
        i++;
    }
            pid = fork();
            if (pid == -1)
                error();
            if (pid == 0)
                parent_process(list_commandes[nb_str(commande, '|')], envp, fd);
            i = 0;
            close(fd[0]);
            close(fd[1]);
            while (i++ < nb_str(commande, '|') + 1)
            {
                wait(NULL);
            }
}

void    ft_redirect_out(char *commande, char **envp)
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
        ft_printf("commande = %s et fd = %d\n", list_command[0], STDOUT_FILENO);
        execute(list_command[0], envp);
        close(fileout);
        dup2(STDOUT_FILENO, STDOUT_FILENO);
    }
    else
        waitpid(pid, &status, 0);
    
}

void    ft_redirect_in(char *commande, char **envp)
{
    char    **list_command;
    pid_t   pid;
    int     filein;
    int     status;
    int     std_in;

    std_in = dup(0);
    list_command = ft_split(commande, '<');
    pid = fork();
    if (pid == -1)
        error();
    if (pid == 0)
    {
        filein = open(list_command[1] + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(std_in, STDIN_FILENO);
        execute(list_command[0], envp);
        close(filein);
        close(std_in);
        dup2(STDIN_FILENO, STDIN_FILENO);
    }
    else
        waitpid(pid, &status, 0);
}