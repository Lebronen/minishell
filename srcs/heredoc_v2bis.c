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

void	restore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

int	isitlast(t_token *token)
{
	token = token->next;
	while (token && token->next && token->type != PIPE)
	{
		if (token->type == REDIR)
			return (0);
		token = token->next;
	}
	return (1);
}

void	ctrl_c_heredoc(int std_in, t_data *data)
{
	dup2(std_in, STDIN_FILENO);
	close(std_in);
	g_sig_handle = 0;
	data->last_error = 130;
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
