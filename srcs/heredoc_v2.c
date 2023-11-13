/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:57:39 by rshay             #+#    #+#             */
/*   Updated: 2023/10/28 14:45:12 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	restore_signal()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

int	isitlast(t_token *token)
{
	token = token->next;
	while(token && token->next && token->type != PIPE)
	{
		if (token->type == REDIR)
			return (0);
		token = token->next;
	}
	return (1);
}

char **manage_heredoc_last(char *endword, t_data *data)
{
	char **heredoc;
	int	i;
	
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler_heredoc);
	i = 0;
	heredoc = malloc(sizeof(char *) * 70);
	if (!heredoc)
	{
		restore_signal();
		return (NULL);
	}
	heredoc[0] = env_value_checker(readline(">"), data);
	while (heredoc[i] && ft_strncmp(heredoc[i], endword, ft_strlen(endword)))
	{
			i++;
			heredoc[i] = env_value_checker(readline(">"), data);
	}
	restore_signal();
	if (heredoc && heredoc[i])
		return(heredoc);
	else
		return (NULL);
}

void	manage_heredoc_notlast(char *endword)
{
	char *heredoc;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler_heredoc);
	heredoc = readline(">");
	while (heredoc && ft_strncmp(heredoc, endword, ft_strlen(endword)))
	{
			free(heredoc);
			heredoc = readline(">");
	}
	if(heredoc)
		free(heredoc);
	restore_signal();
}


void	manage_heredoc(t_node *node, t_token *token, t_data *data)
{
	int i;
	int	std_in;
	
	std_in = dup(STDIN_FILENO);
	if (node->fd_in != -2)
	{
		close(std_in);
		node->heredoc = NULL;
		return ;
	}
	i = 0;
	while (token && token->next && token->type != PIPE)
	{
		if (token->type_2 == ENDOF && !isitlast(token))
			manage_heredoc_notlast(token->next->str);
		else if (token->type_2 == ENDOF && isitlast(token))
			node->heredoc = manage_heredoc_last(token->next->str, data);
		if (g_sig_handle == 1500)
		{
			dup2(std_in, STDIN_FILENO);
			close(std_in);
			g_sig_handle = 1;
			node->heredoc = NULL;
			return ;
		}
		else if (!node->heredoc)
		{
			node->heredoc = NULL;
			printf("warning: here-document delimited by end-of-file (wanted: %s)\n", token->next->str);
			return ;
		}
		token = token->next;
	}
	close(std_in);
}

//attention node->heredoc a free plus tard