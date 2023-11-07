/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:10:40 by rshay             #+#    #+#             */
/*   Updated: 2023/11/02 19:26:11 by lebronen         ###   ########.fr       */
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

void	child_process(t_node *node, t_list *envp, int *fd)
{
	dup2(fd[1], STDOUT_FILENO);
	dup2(node->fd_in, STDIN_FILENO);
	close(fd[0]);
	execute(node->str_options, envp);
}

void	parent_process(t_node *node, t_list *envp, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(node->fd_out, STDOUT_FILENO);
	close(fd[1]);
	execute(node->str_options, envp);
}

void	pipe_process(t_node *node, t_list *envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(node->str_options, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
        wait(NULL);
	}
}

void    ft_pipe(t_node *node, t_list *envp)
{
    t_node  *current;
    
    current = node;
    dup2(current->fd_in, STDIN_FILENO);
    while (current->next)
    {
        pipe_process(current, envp);    
        current = current->next;
    }
    dup2(current->fd_out, STDOUT_FILENO);
    execute(current->str_options, envp);
    wait(NULL);
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