/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:25:00 by cgermain          #+#    #+#             */
/*   Updated: 2023/12/19 16:50:18 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_node *node)
{
	while (node)
	{
		if (node->fd_in == -1 || node->fd_out == -1)
			return (0);
		if (node->fd_in == -2 && node->heredoc == NULL)
			return (0);
		node = node->next;
	}
	return (1);
}

void	init_read(t_token **token, t_node **node)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler);
	*token = NULL;
	*node = NULL;
}

void	free_all(char *commande, t_token *token, t_node *node)
{
	if (commande)
		free(commande);
	if (token)
		free_lexer(token);
	if (node)
		free_nodes(node);
}

void	prompt(t_data *data, int in, int out)
{
	char	*commande;
	t_token	*token;
	t_node	*node;

	while (1)
	{
		init_read(&token, &node);
		commande = readline("Minishell~$");
		if (no_command(commande))
			break ;
		while (error_cmd(commande, data))
		{
			add_history(commande);
			commande = manage_error_cmd(commande);
			if (no_command(commande))
				break ;
		}
		if (!commande)
			break ;
		add_history(commande);
		if (init_node(&commande, &token, &node, data) && check_heredoc(node))
			process(node, data, in, out);
		free_all(commande, token, node);
	}
	rl_clear_history();
}
