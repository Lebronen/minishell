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

char	**end_manage_heredoc(char **heredoc, int i)
{
	free(heredoc[i]);
	heredoc[i] = NULL;
	restore_signal();
	return (heredoc);
}

char	**manage_heredoc_last(char *endword, t_data *data)
{
	char	**heredoc;
	int		i;

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
	if (!heredoc[0])
		return (end_heredoc(heredoc, 0));
	while (heredoc[i] && ft_strncmp(heredoc[i], endword, ft_strlen(endword)))
	{
			i++;
			heredoc[i] = env_value_checker(readline(">"), data);
		if (!heredoc[i])
			return (end_heredoc(heredoc, i));
	}
	return (end_manage_heredoc(heredoc, i));
}

void	manage_heredoc_notlast(char *endword)
{
	char	*heredoc;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler_heredoc);
	heredoc = readline(">");
	while (heredoc && ft_strncmp(heredoc, endword, ft_strlen(endword)))
	{
		free(heredoc);
		heredoc = readline(">");
	}
	if (heredoc)
		free(heredoc);
	restore_signal();
}

void	manage_heredoc(t_node *node, t_token *token, t_data *data)
{
	int	i;
	int	std_in;

	std_in = dup(STDIN_FILENO);
	i = 0;
	while (node->fd_in == -2 && token && token->next && token->type != PIPE)
	{
		if (token->type_2 == ENDOF && !isitlast(token))
			manage_heredoc_notlast(token->next->str);
		else if (token->type_2 == ENDOF && isitlast(token))
			node->heredoc = manage_heredoc_last(token->next->str, data);
		if (token->type_2 == ENDOF && isitlast(token) && !node->heredoc)
		{
			if (g_sig_handle == SIGINT)
				ctrl_c_heredoc(std_in, data);
			else
				ctrl_d_heredoc(token->next->str, data);
			node->heredoc = NULL;
			return ;
		}
		token = token->next;
	}
	close(std_in);
}
