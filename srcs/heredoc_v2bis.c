/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_v2bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:26:01 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/13 15:26:03 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isitlast(t_token *token)
{
	int	type;

	type = token->type_2;
	token = token->next;
	while (token && token->next && token->type != PIPE)
	{
		if (token->type_2 == type)
			return (0);
		token = token->next;
	}
	return (1);
}

int	end_error_heredoc(t_node *node)
{
	node->fd_in = 0;
	node->fd_out = 1;
	node->heredoc = NULL;
	return (0);
}

int	ctrl_c_heredoc(int std_in, t_data *data, t_node *node)
{
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	data->last_error = 130;
	g_sig_handle = 0;
	return (end_error_heredoc(node));
}

void	ctrl_d_heredoc(char *str, t_data *data)
{
	printf("warning: here-document delimited by end-of-file ");
	printf("(wanted: %s)\n", str);
	data->last_error = 0;
}

char	**end_heredoc(char **heredoc, int i)
{
	while (i >= 0)
	{
		free(heredoc[i]);
		i --;
	}
	free(heredoc);
	restore_signal();
	return (NULL);
}
