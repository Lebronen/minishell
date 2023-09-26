/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:32 by rshay             #+#    #+#             */
/*   Updated: 2023/09/26 15:42:29 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>

#define PIPE 0
#define REDIR 1
#define WORD 2
#define QUOTE 3

# define IN 0
# define OUT 1
# define ENDOF 2
# define APPEND 3

# define PATH 0
# define COMMAND 1
# define OPTION 2
# define ARG 3

typedef struct s_token
{
	int	type;
	int	type_2;
	char	*str;

	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

void    prompt(char **envp);
void    execute(char *commande, char **envp);
void	error(void);
char	*find_path(char *cmd, char **envp);
int     nb_str(char *s, char c);
void    ft_pipe(char *commande, char **envp);
void	process(char *commande, char **envp);
int	    open_file(char *argv, int i);
void    ft_redirect_out(char *commande, char **envp);
void    ft_redirect_in(char *commande, char **envp);
char    **init_env(char **envp);
void    ft_double(char *commande, char **envp);
t_token *lexer(char *commande, char **envp);
void print_token(t_token *token);
char	*get_env_value(char **envp, char *name);
void    cd(char *path);
void    pwd();
void    env(char **envp);
void    echo(char *str, int option, int fd);

#endif
