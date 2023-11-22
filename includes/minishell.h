/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:49:46 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/22 16:23:28 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <errno.h>
# include <signal.h>

# define PIPE 0
# define REDIR 1
# define WORD 2
# define QUOTE 3

# define IN 0
# define OUT 1
# define ENDOF 2
# define APPEND 3

# define PATH 4
# define COMMAND 5
# define OPTION 6
# define ARG 7

# define PIP 0
# define RDR 1
# define CMD 2

extern int	g_sig_handle;

typedef struct s_data
{
	int		last_error;
	int		signal;
	t_list	*envp;
}	t_data;

typedef struct s_token
{
	int				type;
	int				type_2;
	char			*str;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_node
{
	int				fd_in;
	int				fd_out;
	char			**str_options;
	char			**heredoc;
	struct s_data	*data;
	struct s_node *prev;
	struct s_node *next;

} t_node;


//ENVIRONMENT
void	env(t_list *envp);
char	**add_env(char *ligne, t_list *envp);
char	**supp_env(char *ligne, t_list *envp);
t_list	*tab_to_list(char **tab);
char	**tabcpy(char **tab);
char	**list_to_tab(t_list *env);
t_list	*ft_lstdupnew(char *content);
void	set_shlvl(t_list *envp);
void	manage_shlvl(char *env, char **result, int j);
void	free_env(char **env);
char	*ft_strdup_c(char *s, char c);
char	*ft_strdup_c2(char *s, char c);
char	*name_cleaner(char *name);
char	*env_value_checker(char *commande, t_data *data);
char	*get_env_value(t_list *envp, char *name);
int		env_value_quote(int i, char **commande, t_list *envp);
char	*new_command(char *commande, char *env_value, int i);
char	**init_env(char **envp);

//ERRORS
int		print_error(int error_num, int fd, char *str, t_data *data);
int		error_cmd(char *commande, t_data *data);
int		input_error(char *str, t_data *data);
int		error_ambig(char *commande, t_data *data);

//REDIRECTIONS + HEREDOCS
void	ctrl_c_heredoc(int std_in, t_data *data);
void	ctrl_d_heredoc(char *str, t_data *data);
char	**end_heredoc(char **heredoc, int i);
int		isitlast(t_token *token);
char	*heredocv2(char *commande);

//SIGNALS
void	restore_signal(void);
void	signal_loop(t_data	*data);
void	signal_handler(int signum);
void	signal_handler_heredoc(int signum);
int		check_signal(void);

//PARSING
void	free_nodes(t_node *node);
t_token	*first_token(t_token *token);
t_token	*new_token(int type, char *str, t_token *last);
int		handlepipetoken(int i, t_token **last);
int		handleinputredir(int i, t_token **last, char *commande);
int		handleoutputredir(int i, t_token **last, char *commande);
int		handledoublequotetoken(int i, t_token **last, char *commande);
int		handlesinglequotetoken(int i, t_token **last, char *commande);
int		handlewordtoken(int i, t_token **last, char *commande);
t_node	*make_cmd(t_token *token);
t_node	*make_pip(t_token *token);
t_node	*make_rdr(t_token *token);
t_token	*previous_cmd(t_token *token);
t_node	*nodizer(t_token *token, t_data *data);
t_node	*init_tree(t_token *token);
t_token	*next_pipe(t_token *token);
void	print_node(t_node *node);
t_token	*lexer(char *commande, t_data *data);
void	print_token(t_token *token);

//EXEC

//UTILS + FREE
void	prompt(t_data *data);
void	execute(char **commande, t_data *data);
void	error();
char	*find_path(char *cmd, char **envp);
int		nb_str(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_index(char *commande, char c);
void	ft_pipe(t_node *node);
void    close_pipes(int **fd, int nb);
void wait_for_childrens(int nb);
void    free_pipes(int **fd, int nb);
int		nb_pipes(t_node *node);
void	process(t_node *node, t_data *data);
int		open_file(char *argv, int i);
void	ft_redirect(t_node *node, t_data *data);
void	cd(char *path);
void	pwd(void);
void	echo(char *str, int option, int fd);
void	export(char *commande, t_list *env);
int		init_out(t_token *token);
int		init_in(t_token *token, t_data *data);
void	free_lexer(t_token *token);
void	manage_heredoc(t_node *node, t_token *token, t_data *data);
void	unset(char *commande, t_list *envp);
void	del(void *content);
int		ft_strcmp(char *s1, char *s2);
int		is_builtin(char **commande, t_data *data);
void	free_data(t_data *data);

#endif
