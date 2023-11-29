/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:25:00 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/29 18:23:20 by rshay            ###   ########.fr       */
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

void	prompt(t_data *data)
{
	char	*commande;
	t_token	*token;
	t_node	*node;
	char	cwd[256];

	while (1)
	{
		init_read(&token, &node);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			print_error(errno, NULL, "cwd error \n", data);
		ft_strlcat(cwd, "~$", 256);
		commande = readline(cwd);
		if (no_command(commande))
			break ;
		while (error_cmd(commande, data))
			commande = manage_error_cmd(commande, cwd);
		if (init_node(&commande, &token, &node, data) && check_heredoc(node))
		{
			data->last_error = 0;
			process(node, data);
			add_history(commande);
		}
		free_all(commande, token, node);
	}
	rl_clear_history();
}
