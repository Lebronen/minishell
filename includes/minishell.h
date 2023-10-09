/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:32 by rshay             #+#    #+#             */
/*   Updated: 2023/10/07 16:56:45 by rshay            ###   ########.fr       */
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

# define PATH 4
# define COMMAND 5
# define OPTION 6
# define ARG 7

#define PIP 0
#define RDR 1
#define CMD 2

typedef struct s_token
{
	int	type;
	int	type_2;
	char	*str;

	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_node
{
	int type;
	int rdr_type;
	char *path;
	char **str_options;
	struct s_node *up;
	struct s_node *left;
	struct s_node *right;
} t_node;


void    prompt(t_list *envp);
void    execute(char *commande, t_list *envp);
void	error(void);
char	*find_path(char *cmd, char **envp);
int     nb_str(char *s, char c);
int		ft_index(char *commande, char c);
void    ft_pipe(char *commande, t_list *envp);
void	process(char *commande, t_list *envp);
int	    open_file(char *argv, int i);
void    ft_redirect_out(char *commande, t_list *envp);
void    ft_redirect_in(char *commande, t_list *envp);
char    **init_env(char **envp);
void    ft_double(char *commande, t_list *envp);
t_token *lexer(char *commande, t_list *envp);
void	print_token(t_token *token);
char	*get_env_value(t_list *envp, char *name);
void    cd(char *path);
void    pwd();
void    env(t_list *envp);
void    echo(char *str, int option, int fd);
void    export(char *commande, t_list *env);
char    **add_env(char *ligne, t_list *envp);
char    **supp_env(char *ligne, t_list *envp);
char    **unset(char *commande, t_list *env);
t_list  *tab_to_list(char **tab);
char    **tabcpy(char **tab);
char    **list_to_tab(t_list *env);
t_list	*ft_lstdupnew(char *content);
t_node  *make_cmd(t_token *token, t_node *up);
t_node  *make_pip(t_token *token);
t_node  *make_rdr(t_token *token);
t_token *previous_cmd(t_token *token);
t_node  *nodizer(t_token *token);
t_node *init_tree(t_token *token);
t_token *next_pipe(t_token *token);
void print_node(t_node *node);
void print_tree(t_node *node);


#endif
