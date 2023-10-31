/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 17:33:32 by rshay             #+#    #+#             */
/*   Updated: 2023/10/28 17:21:06 by rshay            ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
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
	int fd_in;
	int	fd_out;
	char **str_options;
	char **heredoc;
	struct s_node *prev;
	struct s_node *next;

} t_node;


void    prompt(t_list *envp);
void    execute(char **commande, t_list *envp);
void	error(void);
char	*find_path(char *cmd, char **envp);
int     nb_str(char *s, char c);
int 	ft_strcmp(char *s1, char *s2);
int		ft_index(char *commande, char c);
void    ft_pipe(t_node *node, t_list *envp);
void	process(t_node *node, t_list *envp);
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
t_list  *tab_to_list(char **tab);
char    **tabcpy(char **tab);
char    **list_to_tab(t_list *env);
t_list	*ft_lstdupnew(char *content);
t_node  *make_cmd(t_token *token);
t_node  *make_pip(t_token *token);
t_node  *make_rdr(t_token *token);
t_token *previous_cmd(t_token *token);
t_node  *nodizer(t_token *token, t_list *envp);
t_node *init_tree(t_token *token);
t_token *next_pipe(t_token *token);
void print_node(t_node *node);
void print_tree(t_node *node);
int     init_out(t_token *token);
int     init_in(t_token *token);
void 	free_lexer(t_token *token);
void    manage_heredoc(t_node *node, t_token *token, t_list *envp);
void    free_nodes(t_node *node);
t_token *first_token(t_token *token);
t_token *new_token(int type, char *str, t_token *last);
int handlepipetoken(int i, t_token **last);
int handleinputredir(int i, t_token **last, char *commande);
int handleoutputredir(int i, t_token **last, char *commande);
int handledoublequotetoken(int i, t_token **last, char *commande);
int handlesinglequotetoken(int i, t_token **last, char *commande);
int	handlewordtoken(int i, t_token **last, char *commande);
char	*ft_strdup_c(char *s, char c);
char	*env_value_checker(char *commande, t_list *envp);
int error_cmd(char *commande);
int input_error(char *str);
int error_ambig(char *commande);
char	*ft_strdup_c2(char *s, char c);
char *name_cleaner(char *name);



void    unset(char *commande, t_list *envp);
void	del(void *content);
int 	get_next_line(char **line);
void    ft_heredoc(char *commande, t_list *envp);
int 	ft_strcmp(char *s1, char *s2);
char	*heredocv2(char *commande);
int     is_builtin(char **commande);

#endif
