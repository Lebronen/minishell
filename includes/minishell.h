/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:49:46 by cgermain          #+#    #+#             */
/*   Updated: 2023/12/05 16:58:28 by rshay            ###   ########.fr       */
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
# include <limits.h>

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
	int		*error_ptr;
	int		malloc_error;
	int		is_env;
	int		is_path;
	int		signal;
	char	*path;
	t_list	*envp;
	int		envlen;
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
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

//ENVIRONMENT
int		env(t_data *data);
char	**add_env(char *ligne, t_list *envp);
char	**supp_env(char *ligne, t_list *envp);
t_list	*tab_to_list(char **tab);
char	**tabcpy(char **tab);
int		tablen(char **tab);
char	**list_to_tab(t_list *env);
t_list	*ft_lstdupnew(char *content);
void	set_shlvl(t_list *envp);
int		manage_shlvl(char *env, char **result, int j);
void	free_env(char **env);
char	*ft_strdup_c(char *s, char c);
char	*ft_strdup_c2(char *s, char c);
char	*ft_strdup_c3(char *s, char c);
char	*name_cleaner(char *name);
char	*env_value_checker(char *commande, t_data *data);
char	*get_env_value(t_list *envp, char *name);
int		env_value_quote(int i, char **commande, t_data *data);
char	*new_command(char *commande, char *env_value, int i);
char	**init_env(char **envp, t_data *data);
char	**create_envp(t_data *data);
int		env_value_dollar(int i, char **commande, t_data *data);
int		env_value_backslash(int i, char **commande);
char	*manage_with_quote(char *commande);
int		has_quote(char *commande);
size_t	boost_i(char *commande, size_t i);
void	free_str(char *str, char *str1);

//ERRORS
int		print_error(int error_num, char *nom, char *str, t_data *data);
int		error_cmd(char *commande, t_data *data);
int		input_error(char *str, t_data *data);
int		error_ambig(char *commande, t_data *data);
int		no_command(char *commande);
char	*manage_error_cmd(char *commande);
int		syntax_error(t_data *data, char *commande, int i);
t_token	*malloc_error_token(t_token *token);

//REDIRECTIONS + HEREDOCS
int		ctrl_c_heredoc(int std_in, t_data *data, t_node *node);
void	ctrl_d_heredoc(char *str, t_data *data);
char	**end_heredoc(char **heredoc, int i);
int		isitlast(t_token *token);
char	*heredocv2(char *commande);
int		end_error_heredoc(t_node *node);
t_node	*node_no_cmd(t_node *node);

//SIGNALS
void	restore_signal(void);
void	signal_loop(t_data	*data);
void	signal_handler(int signum);
void	signal_handler_exec(int signum);
void	signal_handler_heredoc(int signum);
int		check_signal(void);
void	sigint_react(t_data *data);

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
int		is_dir(char *commande);
t_token	*previous_cmd(t_token *token);
t_node	*nodizer(t_token *token, t_data *data);
t_node	*init_tree(t_token *token);
t_token	*next_pipe(t_token *token);
void	print_node(t_node *node);
t_token	*lexer(char *commande, t_data *data);
void	print_token(t_token *token);
int		init_node(char	**commande, t_token **token,
			t_node **node, t_data *data);
int		has_prev_cmd(t_token *token);
t_node	*error_malloc_node(t_node *node);
void	handlenothing(t_token **last);
int		is_n_good(char *str);

//UTILS + FREE
void	prompt(t_data *data, int in, int out);
void	execute(char **commande, t_data *data);
void	error(t_data *data);
char	*find_path(char *cmd, char **envp);
int		nb_str(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_index(char *commande, char c);
void	ft_pipe(t_node *node, int *fd1, int *fd2, int nb);
void	close_pipes(int *fd1, int *fd2, int i);
int		wait_for_childrens(int nb);
int		nb_pipes(t_node *node);
void	process(t_node *node, t_data *data, int in, int out);
int		open_file(char *argv, int i);
void	ft_redirect_in(t_node *node, t_data *data);
void	ft_redirect_out(t_node *node);
int		cd(char *path, t_data *data);
int		update_pwd(char *cwd, t_data *data);
int		pwd(void);
int		echo(char **str, int option, int fd);
int		n_parsing(char **str);
int		ft_str_only_ncmp(char *s1, char *s2, int n);
int		export(char *commande, t_data *data);
void	loop_export(char **commande, t_data *data);
int		ft_strlencmp(char *s1, char *s2, int ind);
char	*trimexport(char *str);
void	ft_exit(char **commande, t_data *data);
int		init_out(t_token *token, int fd_in);
int		init_in(t_token *token, t_data *data);
void	free_lexer(t_token *token);
int		manage_heredoc(t_node *node, t_token *token, t_data *data);
void	loop_unset(char **commande, t_data *data);
int		unset(char *commande, t_data *data);
void	del(void *content);
int		ft_strcmp(char *s1, char *s2);
void	is_builtin_exec(char **commande, t_data *data);
int		is_builtin(char **commande);
void	free_data(t_data *data);
int		is_only_builtin(char **commande);
int		ft_heredoc(t_node *node, t_data *data);
void	exec_cmd(t_node *node, t_data *data);
void	execloop(t_node *node, int in, int out);
void	pipe_process(t_node *tmp, int *fd1, int *fd2, int nb);
void	pipe_loop(t_node *tmp, int *fd1, int *fd2, int j);
void	child_process(t_node *tmp, int *fd1, int *fd2, int i);
int		only_export(t_data *data);
void	free_first(t_list **current);
void	free_heredoc(t_node *node);
int		ft_strcmp2(char *s1, char *s2);
t_list	*remove_first(t_list *head, char *commande);
void	remove_loop(t_data *data, char *commande);

#endif
