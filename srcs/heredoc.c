/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:57:39 by rshay             #+#    #+#             */
/*   Updated: 2023/10/14 17:33:21 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    while (*s1 || *s2)
    {
        if (*s1 != *s2)
            return (1);
    }
    return (0);
}

int get_next_line(char **line)
  {
      char    *buffer;
      int     i;
      int     r;
      char    c;
  
      i = 0;
      r = 0;
      buffer = (char *)malloc(10000);
      if (!buffer)
          return (-1);
      r = read(0, &c, 1);
      while (r && c != '\n' && c != '\0')
      {
          if (c != '\n' && c != '\0')
              buffer[i] = c;
          i++;
          r = read(0, &c, 1);
      }
      buffer[i] = '\n';
      buffer[++i] = '\0';
      *line = buffer;
      free(buffer);
      return (r);
  }
  
  void    ft_heredoc(char *commande, t_list *envp)
{
    pid_t   reader;
    char    **parts;
    char    *line;

    parts = ft_split(commande, '<');
    reader = fork();
    if (reader == 0)
    {
        while (get_next_line(&line))
        {
            if (ft_strcmp(line, parts[1]))
                exit(EXIT_SUCCESS);
            write(1, line, ft_strlen(line));
        }
    }
    else
    {
        wait(NULL);
    }
    
    execute(parts[0], envp);
}