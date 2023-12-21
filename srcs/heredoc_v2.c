/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:57:39 by rshay             #+#    #+#             */
/*   Updated: 2023/12/19 10:37:34 by rshay            ###   ########.fr       */
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
	while (heredoc[i] && ft_strcmp(heredoc[i], endword))
	{
			i++;
			heredoc[i] = env_value_checker(readline(">"), data);
		if (!heredoc[i])
			return (end_heredoc(heredoc, i));
	}
	return (end_manage_heredoc(heredoc, i));
}

void	manage_heredoc_notlast(char *endword, t_data *data)
{
	char	*heredoc;

	heredoc = NULL;
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler_heredoc);
	if (g_sig_handle != SIGINT)
		heredoc = readline(">");
	if (!heredoc && g_sig_handle != SIGINT)
		ctrl_d_heredoc(endword, data);
	while (heredoc && ft_strcmp(heredoc, endword))
	{
		free(heredoc);
		heredoc = readline(">");
		if (!heredoc && g_sig_handle != SIGINT)
			ctrl_d_heredoc(endword, data);
	}
	if (heredoc)
		free(heredoc);
	restore_signal();
}

int	manage_heredoc(t_node *node, t_token *token, t_data *data)
{
	int	std_in;

	node->heredoc = NULL;
	std_in = dup(STDIN_FILENO);
	while (node && token && token->next && token->type != PIPE)
	{
		if (token->type_2 == ENDOF && !isitlast(token))
			manage_heredoc_notlast(token->next->str, data);
		else if (token->type_2 == ENDOF && isitlast(token))
			node->heredoc = manage_heredoc_last(token->next->str, data);
		if (token->type_2 == ENDOF && !node->heredoc)
		{
			if (g_sig_handle == SIGINT)
				return (ctrl_c_heredoc(std_in, data, node));
			else if (isitlast(token))
			{
				ctrl_d_heredoc(token->next->str, data);
				return (end_error_heredoc(node));
			}		
		}
		token = token->next;
	}
	close(std_in);
	return (1);
}
