/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:25:00 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/29 15:27:28 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_node *node)
{
	while (node)
	{
		if (node->fd_in == -2 && node->heredoc == NULL)
			return (0);
		node = node->next;
	}
	return (1);
}

void	init_read(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

void	free_all(char *commande, t_token *token, t_node *node)
{
	free(commande);
	free_lexer(token);
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
		init_read();
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			print_error(errno, 2, "cwd error \n", data);
		ft_strlcat(cwd, "~$", 256);
		commande = readline(cwd);
		if (no_command(commande))
			break ;
		while (error_cmd(commande, data))
			commande = manage_error_cmd(commande, cwd);
		init_node(&commande, &token, &node, data);
		if (check_heredoc(node))
		{
			process(node, data);
			add_history(commande);
		}
		free_all(commande, token, node);
	}
	rl_clear_history();
}
