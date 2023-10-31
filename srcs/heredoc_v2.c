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

char **manage_heredoc_last(char *endword, t_list *envp)
{
	char **heredoc;
	int	i;

	i = 0;
	heredoc = malloc(sizeof(char *) * 70);
	heredoc[0] = env_value_checker(readline(">"), envp);
	while (ft_strncmp(heredoc[i], endword, ft_strlen(endword)))
	{
			i++;
			heredoc[i] = env_value_checker(readline(">"), envp);
	}
	return(heredoc);
}

void	manage_heredoc_notlast(char *endword)
{
	char *heredoc;

	heredoc = readline(">");
	while (ft_strncmp(heredoc, endword, ft_strlen(endword)))
	{
            free(heredoc);
			heredoc = readline(">");
	}
	free(heredoc);
}


void	manage_heredoc(t_node *node, t_token *token, t_list *envp)
{
	int i;

	if (node->fd_in != -2)
		node->heredoc = NULL;
	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type_2 == ENDOF && !isitlast(token))
			manage_heredoc_notlast(token->next->str);
		if (token->type_2 == ENDOF && isitlast(token))
			node->heredoc = manage_heredoc_last(token->next->str, envp);
		token = token->next;
	}
}


