/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:57:39 by rshay             #+#    #+#             */
/*   Updated: 2023/10/28 14:45:12 by rshay            ###   ########.fr       */
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
  void    ft_heredoc(char *commande, t_list *envp)
{
    int     pipefd[2];
    pid_t   child_pid;
    int     status;
    char    **parts;
    
    parts = ft_split(commande, '<');
    if (pipe(pipefd) == -1) {
        perror("Erreur lors de la création du tube");
        return;
    }
     child_pid = fork();
    
    if (child_pid == -1) {
        perror("Erreur lors de la création du processus fils");
        return;
    } else if (child_pid == 0) { 
        close(pipefd[1]); 
        
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("Erreur lors de la redirection de l'entrée standard");
            exit(1);
        }
        close(pipefd[0]);
        execute(parts[0], envp);
        perror("Erreur lors de l'exécution de la commande");
        exit(1);
    } else {
        close(pipefd[0]);

        char *heredoc_content = NULL;
        size_t heredoc_size = 0;
        char buffer[1024];

        while (1) {
            ft_printf("> ");
            ssize_t bytes_read = read(STDIN_FILENO, buffer, 1024);
            if (bytes_read < 0) {
                perror("Erreur de lecture");
                free(heredoc_content);
                return;
            } else if (bytes_read == 0) {
                break;
            }
            if (ft_strncmp(buffer, parts[1], strlen(parts[1])) == 0) {
                break;
            }
            char *temp = (char *)realloc(heredoc_content, heredoc_size + bytes_read);
            if (temp == NULL) {
                perror("Allocation mémoire échouée");
                free(heredoc_content);
                return;
            }
            heredoc_content = temp;
            ft_memcpy(heredoc_content + heredoc_size, buffer, bytes_read);
            heredoc_size += bytes_read;
        }
        write(pipefd[1], heredoc_content, heredoc_size);
        close(pipefd[1]);
        wait(&status);
        free(heredoc_content);
    }
}